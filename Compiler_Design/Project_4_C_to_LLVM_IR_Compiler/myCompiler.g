grammar myCompiler;

options {
	language = Java;
}

@header {
    // import packages here. (depends on language)
	import java.util.HashMap;
	import java.util.ArrayList;
}

@members {  // you can treat it as global variable.
	boolean TRACEON = false;
	boolean IS_PRINTF = false;
	public enum Type {
		ERR, BOOL, INT, DOUBLE, CHAR, STRING, FUNC;
	}
	class tVar {
		String name;
		int intValue;
		double doubleValue;
	};
	class Info {
		Type theType;
		tVar theVar;

		Info() {
			theType = Type.ERR;
			theVar = new tVar();
		}
	};
	HashMap<String, Info> symtab = new HashMap<>();
	ArrayList<String> textCode = new ArrayList<>();
	int valCnt = 0;
	int labelCnt = 0;
	int strCnt = 0;
	int tabCnt = 0;
	int attr = 0;
}

translationUnit
	: externalDeclaration
	| translationUnit externalDeclaration
	| INCLUDE_ (INCLUDE_LIB | INCLUDE_OWN)
	;

externalDeclaration
	: functionDefinition
	| declaration
	;

functionDefinition
	: declarationSpecifiers declarator declarationList compoundStatement
	| declarationSpecifiers {
		System.out.print("define dso_local ");
		if ($declarationSpecifiers.type == Type.INT) {
			System.out.print("i32");
		}
		System.out.flush();
	} declarator {
		++tabCnt;
	} compoundStatement {
		--tabCnt;
		System.out.println("}");
		if (IS_PRINTF) {
			System.out.println("declare i32 @printf(i8*, ...) #" + attr);
			System.out.println("attributes #1 = { \"frame-pointer\"=\"all\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" }");
		}
		for (int i = 0; i < textCode.size(); ++i) {
			System.out.println(textCode.get(i));
		}
	}
	// | declarator declarationList compoundStatement // NOT in GNU C99
	// | declarator compoundStatement; // NOT in GNU C99
	;

declarationList
	: declaration
	| declarationList declaration
	;

primaryExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: ID {
		$theInfo.theType = Type.ERR;
		$theInfo.theVar.name = $ID.text;
		$theInfo.theVar.intValue = 0;
		$theInfo.theVar.doubleValue = 0.0;
	}
	| DEC_NUM {
		$theInfo.theType = Type.INT;
		$theInfo.theVar.name = null;
		$theInfo.theVar.intValue = Integer.parseInt($DEC_NUM.text);
		$theInfo.theVar.doubleValue = Double.valueOf(Integer.parseInt($DEC_NUM.text));
	}
	| FLOAT_NUM
	| STRING {
		Info ii = new Info();
		final String strName = ".str." + strCnt++;
		String str = $STRING.text;
		String subStr = "";
		String code = "@";
		int strLen = str.length();
		int slashCnt = 0;
		str = str.substring(0, strLen - 1);  // remove "
		for (int i = 0; i < str.length(); ++i) {
			if (str.charAt(i) == '\\') {
				++slashCnt;
				char c = str.charAt(i + 1);
				subStr = str.substring(i + 2, str.length());
				str = str.substring(0, i + 1);
				if (c == 'n') {
					str += "0A";
				} else if (c == 't') {
					str += "09";
				} else if (c == 'r') {
					str += "0D";
				} else if (c == '0') {
					str += "00";
				}
				str += subStr;
			}
		}
		str += "\\00\"";  // add \00 and "
		strLen -= 2;  // don't count "
		strLen = strLen - slashCnt + 1;  // +1 is for \00

		ii.theType = Type.STRING;
		ii.theVar.name = strName;
		ii.theVar.intValue = strLen;
		ii.theVar.doubleValue = 0.0;
		symtab.put(strName, ii);

		code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
		textCode.add(code);

		$theInfo = ii;
	}
	| CHAR {
		$theInfo.theType = Type.CHAR;
		$theInfo.theVar.name = $CHAR.text;
		$theInfo.theVar.intValue = 0;
		$theInfo.theVar.doubleValue = 0.0;
	}
	| '(' expr ')' {
		$theInfo = $expr.theInfo;
	}
	;

postfixExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: PRINTF '(' STRING ')' {
		IS_PRINTF = true;
		final String ret = "t" + valCnt++;
		final String strName = ".str." + strCnt++;
		String str = $STRING.text;
		String subStr = "";
		String code = "@";
		int strLen = str.length();
		int slashCnt = 0;
		str = str.substring(0, strLen - 1);  // remove "
		for (int i = 0; i < str.length(); ++i) {
			if (str.charAt(i) == '\\') {
				++slashCnt;
				char c = str.charAt(i + 1);
				subStr = str.substring(i + 2, str.length());
				str = str.substring(0, i + 1);
				if (c == 'n') {
					str += "0A";
				} else if (c == 't') {
					str += "09";
				} else if (c == 'r') {
					str += "0D";
				} else if (c == '0') {
					str += "00";
				}
				str += subStr;
			}
		}
		str += "\\00\"";  // add \00 and "
		strLen -= 2;  // don't count "
		strLen = strLen - slashCnt + 1;  // +1 is for \00

		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0))");
		code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
		textCode.add(code);
	}
	| PRINTF '(' STRING ',' r1 = assignExpr ')' {
		IS_PRINTF = true;
		final String ret = "t" + valCnt++;
		final String strName = ".str." + strCnt++;
		String str = $STRING.text;
		String subStr = "";
		String code = "@";
		int strLen = str.length();
		int slashCnt = 0;
		str = str.substring(0, strLen - 1);  // remove "
		for (int i = 0; i < str.length(); ++i) {
			if (str.charAt(i) == '\\') {
				++slashCnt;
				char c = str.charAt(i + 1);
				subStr = str.substring(i + 2, str.length());
				str = str.substring(0, i + 1);
				if (c == 'n') {
					str += "0A";
				} else if (c == 't') {
					str += "09";
				} else if (c == 'r') {
					str += "0D";
				} else if (c == '0') {
					str += "00";
				}
				str += subStr;
			}
		}
		str += "\\00\"";  // add \00 and "
		strLen -= 2;  // don't count "
		strLen = strLen - slashCnt + 1;  // +1 is for \00

		Info i1 = $r1.theInfo;
		if (i1.theVar.name == null && i1.theType == Type.INT) {
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 " + i1.theVar.intValue + ")");
			code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
			textCode.add(code);
		} else {
			Info i = symtab.get(i1.theVar.name);
			if (i == null) {
				System.err.println("PRINTF1: undefined var: " + i1.theVar.name);
			} else if (i.theType == Type.INT){
				final String a = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a + " = load i32, i32* %" + i.theVar.name);
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 %" + a + ")");
				code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
				textCode.add(code);
			} else if (i.theType == Type.STRING) {
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0)" + ", " + "i8* getelementptr inbounds ([" + i.theVar.intValue + " x i8], [" + i.theVar.intValue + " x i8]* @" + i.theVar.name + ", i64 0, i64 0)" + ")");
				code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
				textCode.add(code);
			} else if (i.theType == Type.BOOL) {
				final String a = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a + " = zext i1 %" + i.theVar.name + " to i32");
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 %" + a + ")");
				code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
				textCode.add(code);
			}
		}
	}
	| PRINTF '(' STRING ',' r1 = assignExpr ',' r2 = assignExpr ')' {
		IS_PRINTF = true;
		final String ret = "t" + valCnt++;
		final String strName = ".str." + strCnt++;
		String str = $STRING.text;
		String subStr = "";
		String code = "@";
		int val1 = 0;
		int val2 = 0;
		int strLen = str.length();
		int slashCnt = 0;
		str = str.substring(0, strLen - 1);  // remove "
		for (int i = 0; i < str.length(); ++i) {
			if (str.charAt(i) == '\\') {
				++slashCnt;
				char c = str.charAt(i + 1);
				subStr = str.substring(i + 2, str.length());
				str = str.substring(0, i + 1);
				if (c == 'n') {
					str += "0A";
				} else if (c == 't') {
					str += "09";
				} else if (c == 'r') {
					str += "0D";
				} else if (c == '0') {
					str += "00";
				}
				str += subStr;
			}
		}
		str += "\\00\"";  // add \00 and "
		strLen -= 2;  // don't count "
		strLen = strLen - slashCnt + 1;  // +1 is for \00

		Info i1 = $r1.theInfo;
		Info i2 = $r2.theInfo;
		if (i1.theVar.name == null && i1.theType == Type.INT && i2.theVar.name == null && i2.theType == Type.INT) {
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 " + i1.theVar.intValue + ", i32 " + i2.theVar.intValue + ")");
			code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
			textCode.add(code);
		} else if (i1.theVar.name != null && i2.theVar.name == null && i2.theType == Type.INT) {
			Info i = symtab.get(i1.theVar.name);
			if (i == null) {
				System.err.println("PRINTF2.1: undefined var: " + i1.theVar.name);
			} else if (i.theType == Type.INT) {
				final String a = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a + " = load i32, i32* %" + i.theVar.name);
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 %" + a + ", i32 " + i2.theVar.intValue + ")");
				code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
				textCode.add(code);
			}
		} else if (i1.theVar.name == null && i1.theType == Type.INT && i2.theVar.name != null) {
			Info j = symtab.get(i2.theVar.name);
			if (j == null) {
				System.err.println("PRINTF2.2: undefined var: " + i2.theVar.name);
			} else if (j.theType == Type.INT) {
				final String a = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a + " = load i32, i32* %" + j.theVar.name);
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 " + i1.theVar.intValue + ", i32 %" + a + ")");
				code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
				textCode.add(code);
			}
		} else if (i1.theVar.name != null && i2.theVar.name != null) {
			Info i = symtab.get(i1.theVar.name);
			Info j = symtab.get(i2.theVar.name);
			final String a1 = "t" + valCnt++;
			final String a2 = "t" + valCnt++;
			if (i == null) {
				System.err.println("PRINTF2.1: undefined var: " + i1.theVar.name);
			} else if (i.theType == Type.INT) {
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a1 + " = load i32, i32* %" + i.theVar.name);
			}
			if (j == null) {
				System.err.println("PRINTF2.2: undefined var: " + i2.theVar.name);
			} else if (j.theType == Type.INT) {
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a2 + " = load i32, i32* %" + j.theVar.name);
			}

			if (i != null && i.theType == Type.INT && j != null && j.theType == Type.INT) {
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + ret + " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + strLen + " x i8], [" + strLen + " x i8]* @" + strName + ", i64 0, i64 0), i32 %" + a1 + ", i32 %" + a2 + ")");
				code = code + strName + " = private unnamed_addr constant [" + strLen + " x i8] c" + str + ", align 1";
				textCode.add(code);
			}
		}
	}
	| PRINTF '(' argumentExprList ')' {
		System.err.println("Not impl. yet.");
	}
	| primaryExpr {
		$theInfo = $primaryExpr.theInfo;
	}
	| postfixExpr '[' expr ']'
	| postfixExpr '(' ')'
	| postfixExpr '(' argumentExprList ')'
	| postfixExpr '.' ID
	| postfixExpr POINTER_OP ID
	| postfixExpr INC_OP
	| postfixExpr DEC_OP
	| '(' typeName ')' '{' initializerList '}' // GNU_C99
	| '(' typeName ')' '{' initializerList ',' '}' // GNU_C99
	;

argumentExprList
	: assignExpr
	| argumentExprList ',' assignExpr
	;

unaryExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: postfixExpr {
		$theInfo = $postfixExpr.theInfo;
	}
	| INC_OP unaryExpr // GNU_C99
	| DEC_OP unaryExpr // GNU_C99
	| unaryOP castExpr
	| SIZEOF_ unaryExpr
	| SIZEOF_ '(' typeName ')'
	;

unaryOP
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

castExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: unaryExpr {
		$theInfo = $unaryExpr.theInfo;
	}
	| '(' typeName ')' castExpr
	;

multiplicativeExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: castExpr {
		$theInfo = $castExpr.theInfo;
	}
	| l1 = multiplicativeExpr '*' r1 = castExpr {
		Info i = new Info();
		Info i1 = symtab.get($l1.theInfo.theVar.name);
		Info i2 = symtab.get($r1.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l1.theInfo.theVar.name == null && $l1.theInfo.theType == Type.INT) {
			val1 = $l1.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr1.1: undefined var: " + $l1.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r1.theInfo.theVar.name == null && $r1.theInfo.theType == Type.INT) {
			val2 = $r1.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr1.2: undefined var: " + $r1.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name == null) {
			i.theVar.intValue = $l1.theInfo.theVar.intValue * $r1.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue * i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = mul nsw i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue * $r1.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = mul nsw i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue * i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = mul nsw i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	| l2 = multiplicativeExpr '/' r2 = castExpr {
		Info i = new Info();
		Info i1 = symtab.get($l2.theInfo.theVar.name);
		Info i2 = symtab.get($r2.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l2.theInfo.theVar.name == null && $l2.theInfo.theType == Type.INT) {
			val1 = $l2.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr2.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r2.theInfo.theVar.name == null && $r2.theInfo.theType == Type.INT) {
			val2 = $r2.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr2.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name == null) {
			i.theVar.intValue = $l2.theInfo.theVar.intValue / $r2.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue / i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = sdiv i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue / $r2.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = sdiv i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue / i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = sdiv i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	| l3 = multiplicativeExpr '%' r3 = castExpr {
		Info i = new Info();
		Info i1 = symtab.get($l3.theInfo.theVar.name);
		Info i2 = symtab.get($r3.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l3.theInfo.theVar.name == null && $l3.theInfo.theType == Type.INT) {
			val1 = $l3.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr1.1: undefined var: " + $l3.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r3.theInfo.theVar.name == null && $r3.theInfo.theType == Type.INT) {
			val2 = $r3.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr1.2: undefined var: " + $r3.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l3.theInfo.theVar.name == null && $r3.theInfo.theVar.name == null) {
			i.theVar.intValue = $l3.theInfo.theVar.intValue % $r3.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l3.theInfo.theVar.name == null && $r3.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l3.theInfo.theVar.intValue % i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = srem i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l3.theInfo.theVar.name != null && $r3.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue % $r3.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = srem i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l3.theInfo.theVar.name != null && $r3.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue % i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = srem i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	;

additiveExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: multiplicativeExpr {
		$theInfo = $multiplicativeExpr.theInfo;
	}
	| l1 = additiveExpr '+' r1 = multiplicativeExpr {
		Info i = new Info();
		Info i1 = symtab.get($l1.theInfo.theVar.name);
		Info i2 = symtab.get($r1.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l1.theInfo.theVar.name == null && $l1.theInfo.theType == Type.INT) {
			val1 = $l1.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr1.1: undefined var: " + $l1.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r1.theInfo.theVar.name == null && $r1.theInfo.theType == Type.INT) {
			val2 = $r1.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr1.2: undefined var: " + $r1.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name == null) {
			i.theVar.intValue = $l1.theInfo.theVar.intValue + $r1.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue + i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = add nsw i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue + $r1.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = add nsw i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue + i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = add nsw i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	| l2 = additiveExpr '-' r2 = multiplicativeExpr {
		Info i = new Info();
		Info i1 = symtab.get($l2.theInfo.theVar.name);
		Info i2 = symtab.get($r2.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l2.theInfo.theVar.name == null && $l2.theInfo.theType == Type.INT) {
			val1 = $l2.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr2.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r2.theInfo.theVar.name == null && $r2.theInfo.theType == Type.INT) {
			val2 = $r2.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr2.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name == null) {
			i.theVar.intValue = $l2.theInfo.theVar.intValue - $r2.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue - i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = sub nsw i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue - $r2.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = sub nsw i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue - i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = sub nsw i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	;

shiftExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: additiveExpr {
		$theInfo = $additiveExpr.theInfo;
	}
	| l1 = shiftExpr RSHIFT_OP r1 = multiplicativeExpr {
		Info i = new Info();
		Info i1 = symtab.get($l1.theInfo.theVar.name);
		Info i2 = symtab.get($r1.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l1.theInfo.theVar.name == null && $l1.theInfo.theType == Type.INT) {
			val1 = $l1.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr1.1: undefined var: " + $l1.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r1.theInfo.theVar.name == null && $r1.theInfo.theType == Type.INT) {
			val2 = $r1.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr1.2: undefined var: " + $r1.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name == null) {
			i.theVar.intValue = $l1.theInfo.theVar.intValue >> $r1.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue >> i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = ashr i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue >> $r1.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = ashr i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue >> i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = ashr i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	| l2 = shiftExpr LSHIFT_OP r2 = multiplicativeExpr {
		Info i = new Info();
		Info i1 = symtab.get($l2.theInfo.theVar.name);
		Info i2 = symtab.get($r2.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l2.theInfo.theVar.name == null && $l2.theInfo.theType == Type.INT) {
			val1 = $l2.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("shiftExpr2.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r2.theInfo.theVar.name == null && $r2.theInfo.theType == Type.INT) {
			val2 = $r2.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("shiftExpr2.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		final String result = "t" + valCnt++;
		i.theType = Type.INT;
		if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name == null) {
			i.theVar.intValue = $l2.theInfo.theVar.intValue << $r2.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + result);
		} else if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue << i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = shl i32 " + val1 + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue << $r2.theInfo.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = shl i32 %" + vl + ", " + val2);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue << i2.theVar.intValue;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = shl i32 %" + vl + ", %" + vr);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 %" + result + ", i32* %" + ret);
		}
		
		$theInfo = i;
	}
	;

relationalExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: shiftExpr {
		$theInfo = $shiftExpr.theInfo;
	}
	| l1 = relationalExpr LT_OP r1 = shiftExpr {
		Info i = new Info();
		Info i1 = symtab.get($l1.theInfo.theVar.name);
		Info i2 = symtab.get($r1.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l1.theInfo.theVar.name == null && $l1.theInfo.theType == Type.INT) {
			val1 = $l1.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("relationalExpr1.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r1.theInfo.theVar.name == null && $r1.theInfo.theType == Type.INT) {
			val2 = $r1.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("relationalExpr1.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		i.theType = Type.BOOL;
		if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name == null) {
			final String result = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue < $r1.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i1, align 1");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i1 " + i.theVar.intValue + ", i1* %" + result);
		} else if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue < i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp slt i32 " + val1 + ", %" + vr);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue < $r1.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp slt i32 %" + vl + ", " + val2);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue < i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp slt i32 %" + vl + ", %" + vr);
		}
		
		$theInfo = i;
	}
	| l2 = relationalExpr GT_OP r2 = shiftExpr {
		Info i = new Info();
		Info i1 = symtab.get($l2.theInfo.theVar.name);
		Info i2 = symtab.get($r2.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l2.theInfo.theVar.name == null && $l2.theInfo.theType == Type.INT) {
			val1 = $l2.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("relationalExpr2.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r2.theInfo.theVar.name == null && $r2.theInfo.theType == Type.INT) {
			val2 = $r2.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("relationalExpr2.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		i.theType = Type.BOOL;
		if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name == null) {
			final String result = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue > $r2.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i1, align 1");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i1 " + i.theVar.intValue + ", i1* %" + result);
		} else if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue > i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sgt i32 " + val1 + ", %" + vr);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue > $r2.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sgt i32 %" + vl + ", " + val2);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue > i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sgt i32 %" + vl + ", %" + vr);
		}
		
		$theInfo = i;
	}
	| l3 = relationalExpr LE_OP r3 = shiftExpr {
		Info i = new Info();
		Info i1 = symtab.get($l3.theInfo.theVar.name);
		Info i2 = symtab.get($r3.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l3.theInfo.theVar.name == null && $l3.theInfo.theType == Type.INT) {
			val1 = $l3.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("relationalExpr1.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r3.theInfo.theVar.name == null && $r3.theInfo.theType == Type.INT) {
			val2 = $r3.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("relationalExpr1.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		i.theType = Type.BOOL;
		if ($l3.theInfo.theVar.name == null && $r3.theInfo.theVar.name == null) {
			final String result = "t" + valCnt++;
			i.theVar.intValue = $l3.theInfo.theVar.intValue <= $r3.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i1, align 1");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i1 " + i.theVar.intValue + ", i1* %" + result);
		} else if ($l3.theInfo.theVar.name == null && $r3.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l3.theInfo.theVar.intValue <= i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sle i32 " + val1 + ", %" + vr);
		} else if ($l3.theInfo.theVar.name != null && $r3.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue <= $r3.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sle i32 %" + vl + ", " + val2);
		} else if ($l3.theInfo.theVar.name != null && $r3.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue <= i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sle i32 %" + vl + ", %" + vr);
		}
		
		$theInfo = i;
	}
	| l4 = relationalExpr GE_OP r4 = shiftExpr {
		Info i = new Info();
		Info i1 = symtab.get($l4.theInfo.theVar.name);
		Info i2 = symtab.get($r4.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l4.theInfo.theVar.name == null && $l4.theInfo.theType == Type.INT) {
			val1 = $l4.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("relationalExpr2.1: undefined var: " + $l4.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r4.theInfo.theVar.name == null && $r4.theInfo.theType == Type.INT) {
			val2 = $r4.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("relationalExpr2.2: undefined var: " + $r4.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		i.theType = Type.BOOL;
		if ($l4.theInfo.theVar.name == null && $r4.theInfo.theVar.name == null) {
			final String result = "t" + valCnt++;
			i.theVar.intValue = $l4.theInfo.theVar.intValue >= $r4.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i1, align 1");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i1 " + i.theVar.intValue + ", i1* %" + result);
		} else if ($l4.theInfo.theVar.name == null && $r4.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l4.theInfo.theVar.intValue >= i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sge i32 " + val1 + ", %" + vr);
		} else if ($l4.theInfo.theVar.name != null && $r4.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue >= $r4.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sge i32 %" + vl + ", " + val2);
		} else if ($l4.theInfo.theVar.name != null && $r4.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue >= i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp sge i32 %" + vl + ", %" + vr);
		}
		
		$theInfo = i;
	}
	;

equalityExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: relationalExpr {
		$theInfo = $relationalExpr.theInfo;
	}
	| l1 = equalityExpr EQ_OP r1 = relationalExpr {
		Info i = new Info();
		Info i1 = symtab.get($l1.theInfo.theVar.name);
		Info i2 = symtab.get($r1.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l1.theInfo.theVar.name == null && $l1.theInfo.theType == Type.INT) {
			val1 = $l1.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("relationalExpr1.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r1.theInfo.theVar.name == null && $r1.theInfo.theType == Type.INT) {
			val2 = $r1.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("relationalExpr1.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		i.theType = Type.BOOL;
		if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name == null) {
			final String result = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue == $r1.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i1, align 1");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i1 " + i.theVar.intValue + ", i1* %" + result);
		} else if ($l1.theInfo.theVar.name == null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l1.theInfo.theVar.intValue == i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp eq i32 " + val1 + ", %" + vr);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue == $r1.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp eq i32 %" + vl + ", " + val2);
		} else if ($l1.theInfo.theVar.name != null && $r1.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue == i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp eq i32 %" + vl + ", %" + vr);
		}
		
		$theInfo = i;
	}
	| l2 = equalityExpr NE_OP r2 = relationalExpr {
		Info i = new Info();
		Info i1 = symtab.get($l2.theInfo.theVar.name);
		Info i2 = symtab.get($r2.theInfo.theVar.name);
		
		String vl = "";
		String vr = "";
		int val1 = 0;
		int val2 = 0;
		
		if ($l2.theInfo.theVar.name == null && $l2.theInfo.theType == Type.INT) {
			val1 = $l2.theInfo.theVar.intValue;
		} else {
			if (i1 == null) {
				System.err.println("relationalExpr2.1: undefined var: " + $l2.theInfo.theVar.name);
			} else if (i1.theType == Type.INT) {
				vl = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = load i32, i32* %" + i1.theVar.name);
			} else if (i1.theType == Type.BOOL) {
				vl = "t" + valCnt++;
				val1 = i1.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vl + " = zext i1 %" + i1.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i1.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		if ($r2.theInfo.theVar.name == null && $r2.theInfo.theType == Type.INT) {
			val2 = $r2.theInfo.theVar.intValue;
		} else {
			if (i2 == null) {
				System.err.println("relationalExpr2.2: undefined var: " + $r2.theInfo.theVar.name);
			} else if (i2.theType == Type.INT) {
				vr = "t" + valCnt++;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = load i32, i32* %" + i2.theVar.name);
			} else if (i2.theType == Type.BOOL) {
				vr = "t" + valCnt++;
				val2 = i2.theVar.intValue;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + vr + " = zext i1 %" + i2.theVar.name + " to i32");
			} else {
				System.err.println("Error, " + i2.theVar.name + "\'s type is not impl. yet. Ignoring loading.");
			}
		}

		i.theType = Type.BOOL;
		if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name == null) {
			final String result = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue != $r2.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = result;
			symtab.put(result, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + result + " = alloca i1, align 1");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i1 " + i.theVar.intValue + ", i1* %" + result);
		} else if ($l2.theInfo.theVar.name == null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = $l2.theInfo.theVar.intValue != i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp ne i32 " + val1 + ", %" + vr);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name == null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue != $r2.theInfo.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp ne i32 %" + vl + ", " + val2);
		} else if ($l2.theInfo.theVar.name != null && $r2.theInfo.theVar.name != null) {
			final String ret = "t" + valCnt++;
			i.theVar.intValue = i1.theVar.intValue != i2.theVar.intValue ? 1 : 0;
			i.theVar.doubleValue = Double.valueOf(i.theVar.intValue);
			i.theVar.name = ret;
			symtab.put(ret, i);
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + ret + " = icmp ne i32 %" + vl + ", %" + vr);
		}
		
		$theInfo = i;
	}
	;

andExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: equalityExpr {
		$theInfo = $equalityExpr.theInfo;
	}
	| andExpr '&' equalityExpr
	;

xorExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: andExpr {
		$theInfo = $andExpr.theInfo;
	}
	| xorExpr '^' andExpr
	;

orExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: xorExpr {
		$theInfo = $xorExpr.theInfo;
	}
	| orExpr '|' xorExpr
	;

logicAndExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: orExpr {
		$theInfo = $orExpr.theInfo;
	}
	| logicAndExpr AND_OP orExpr
	;

logicOrExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: logicAndExpr {
		$theInfo = $logicAndExpr.theInfo;
	}
	| logicOrExpr OR_OP orExpr
	;

conditionExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: logicOrExpr {
		$theInfo = $logicOrExpr.theInfo;
	}
	| logicOrExpr '?' expr ':' conditionExpr
	;

assignExpr returns [Info theInfo] @init { $theInfo = new Info(); }
	: conditionExpr {
		$theInfo = $conditionExpr.theInfo;
		if (TRACEON) {
			System.out.println("assignExpr get conditionExpr: name: " + $theInfo.theVar.name + " , val: " + $theInfo.theVar.intValue);
		}
	}
	| unaryExpr assignOP r1 = assignExpr {
		Info ii = symtab.get($unaryExpr.theInfo.theVar.name);
		if (ii != null) {
			if ($r1.theInfo.theVar.name == null && $r1.theInfo.theType == Type.INT) {
				if (ii.theType != $r1.theInfo.theType) {
					System.err.println("Type is not match, " + $unaryExpr.theInfo.theVar.name + ": " + $unaryExpr.theInfo.theType + ", whereas " + $r1.theInfo.theVar.intValue + ": " + $r1.theInfo.theType);
				} else if ($assignOP.assign == "=") {
					Info i = new Info();
					i.theType = $r1.theInfo.theType;
					i.theVar.name = $unaryExpr.theInfo.theVar.name;
					i.theVar.intValue = $r1.theInfo.theVar.intValue;
					i.theVar.doubleValue = $r1.theInfo.theVar.doubleValue;
					symtab.replace(i.theVar.name, i);
					if (TRACEON) {
						System.out.println("Assign var " + i.theVar.name + " = " + i.theVar.intValue + ", type: " + i.theType);
					}
					for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
					System.out.println("store i32 " + i.theVar.intValue + ", i32* %" + i.theVar.name);
					$theInfo = i;
				} else {
					System.err.println("Got assignOP: " + $assignOP.assign + ", not impl. yet.");
				}
			} else if ($r1.theInfo.theVar.name != null) {
				Info init = symtab.get($r1.theInfo.theVar.name);
				if (init == null) {
					System.err.println("assignExpr: undefined var: " + $r1.theInfo.theVar.name);
				} else if (init.theType != ii.theType) {
					System.err.println("Type is not match, " + $unaryExpr.theInfo.theVar.name + ": " + $unaryExpr.theInfo.theType + ", whereas " + $r1.theInfo.theVar.name + ": " + $r1.theInfo.theType);
				} else if ($assignOP.assign == "=") {
					Info i = new Info();
					String a = "t" + valCnt++;
					i = init;
					for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
					System.out.println("%" + a + " = load i32, i32* %" + init.theVar.name);
					for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
					System.out.println("store i32 %" + a + ", i32* %" + $unaryExpr.theInfo.theVar.name);
					i.theVar.name = $unaryExpr.theInfo.theVar.name;
					symtab.replace($unaryExpr.theInfo.theVar.name, i);
					if (TRACEON) {
						System.out.println("Assign var " + $unaryExpr.theInfo.theVar.name + " = " + init.theVar.name + " = " + init.theVar.intValue + ", type: " + init.theType);
					}
					$theInfo = i;
				} else {
					System.err.println("Got assignOP: " + $assignOP.assign + ", not impl. yet.");
				}
			}
		} else {
			System.err.println("assignExpr: undefined var: " + $unaryExpr.theInfo.theVar.name);
		}
	}
	;

assignOP returns [String assign]
	: '=' { $assign = "="; }
	| RIGHT_ASSIGN { $assign = $RIGHT_ASSIGN.text; }
	| LEFT_ASSIGN { $assign = $LEFT_ASSIGN.text; }
	| ADD_ASSIGN { $assign = $ADD_ASSIGN.text; }
	| SUB_ASSIGN { $assign = $SUB_ASSIGN.text; }
	| MUL_ASSIGN { $assign = $MUL_ASSIGN.text; }
	| DIV_ASSIGN { $assign = $DIV_ASSIGN.text; }
	| MOD_ASSIGN { $assign = $MOD_ASSIGN.text; }
	| AND_ASSIGN { $assign = $AND_ASSIGN.text; }
	| OR_ASSIGN { $assign = $OR_ASSIGN.text; }
	| XOR_ASSIGN { $assign = $XOR_ASSIGN.text; }
	;

expr returns [Info theInfo] @init { $theInfo = new Info(); }
	: assignExpr {
		$theInfo = $assignExpr.theInfo;
	}
	| expr ',' assignExpr
	;

declaration
	: declarationSpecifiers ';'
	| declarationSpecifiers initDeclaratorList[$declarationSpecifiers.type] ';' {
		
	}
	;

declarationSpecifiers returns [Type type]
	: storageClassSpecifier
	| storageClassSpecifier declarationSpecifiers
	| typeSpecifier {
		$type = $typeSpecifier.type;
	}
	| typeSpecifier declarationSpecifiers
	| typeQuantifier
	| typeQuantifier declarationSpecifiers
	;

initDeclaratorList [Type type]
	: initDeclarator [$type] moreDeclaratorList [$type]
	;

moreDeclaratorList [Type type]  // Eliminating left recursion
	: ',' initDeclarator [$type] moreDeclaratorList [$type]
	|
	;

initDeclarator [Type type]
	: declarator {
		Info i = new Info();
		i.theType = $type;
		i.theVar.name = $declarator.name;
		i.theVar.intValue = 0;
		i.theVar.doubleValue = 0.0;
		symtab.put($declarator.name, i);
		if (TRACEON) {
			System.out.println("Initial var " + $declarator.name + " = 0, type: " + $type);
		}
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("%" + $declarator.name + " = alloca i32, align 4");
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("store i32 0, i32* %" + $declarator.name);
	}
	| l1 = declarator '=' initializer {
		if ($initializer.theInfo.theVar.name == null && $initializer.theInfo.theType == Type.INT) {
			Info i = new Info();
			i.theType = $type;
			i.theVar.name = $declarator.name;
			i.theVar.intValue = $initializer.theInfo.theVar.intValue;
			i.theVar.doubleValue = $initializer.theInfo.theVar.doubleValue;
			symtab.put($declarator.name, i);
			if (TRACEON) {
				System.out.println("Initial var " + $declarator.name + " = " + $initializer.theInfo.theVar.intValue + ", type: " + $type);
			}
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("%" + $declarator.name + " = alloca i32, align 4");
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("store i32 " + $initializer.theInfo.theVar.intValue + ", i32* %" + $declarator.name);
		} else if ($initializer.theInfo.theVar.name != null) {
			Info init = symtab.get($initializer.theInfo.theVar.name);
			if (init == null) {
				System.err.println("initDeclarator: undefined var: " + $initializer.theInfo.theVar.name);
			} else if (init.theType != $type) {
				System.err.println("Type is not match, " + $declarator.name + ": " + $type + ", whereas " + init.theVar.name + ": " + init.theType);
			} else {
				Info i = new Info();
				String a = "t" + valCnt++;
				i = init;
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + $declarator.name + " = alloca i32, align 4");
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("%" + a + " = load i32, i32* %" + init.theVar.name);
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("store i32 %" + a + ", i32* %" + $declarator.name);
				i.theVar.name = $declarator.name;
				symtab.put($declarator.name, i);
				if (TRACEON) {
					System.out.println("Initial var " + $declarator.name + " = " + init.theVar.name + " = " + init.theVar.intValue + ", type: " + $type);
				}
			}
		}
	}
	;

storageClassSpecifier
	: TYPEDEF_
	| EXTERN_TYPE
	| STATIC_
	| REGISTER_
	;

typeSpecifier returns [Type type]
	: VOID_TYPE
	| CHAR_TYPE
	| SHORT_TYPE
	| INT_TYPE {
		$type = Type.INT;
	}
	| LONG_TYPE
	| FLOAT_TYPE
	| DOUBLE_TYPE
	| SIGNED_TYPE
	| UNSIGNED_TYPE
	| structOrUnionSpecifier
	| enumSpecifier
	;

typeQuantifier
	: CONST_TYPE
	| VOLATILE_TYPE
	;

structOrUnion
	: STRUCT_
	| UNION_
	;

structOrUnionSpecifier
	: structOrUnion ID '{' structDeclarationList '}'
	// | structOrUnion ID '{' '}'  // New define
	| structOrUnion '{' structDeclarationList '}'
	| structOrUnion ID
	;

structDeclarationList
	: structDeclaration
	| structDeclarationList structDeclaration
	| // New define
	;

structDeclaration
	: specifierQuantifierList structDeclaratorList ';'
	;

specifierQuantifierList
	: typeSpecifier
	| typeSpecifier specifierQuantifierList
	| typeQuantifier
	| typeQuantifier specifierQuantifierList
	;

structDeclaratorList
	: structDeclarator
	| structDeclaratorList ',' structDeclarator
	;

structDeclarator
	: declarator
	| ':' conditionExpr
	| declarator ':' conditionExpr
	;

enumSpecifier
	: ENUM_ '{' enumeratorList '}'
	| ENUM_ ID '{' enumeratorList '}'
	| ENUM_ '{' enumeratorList ',' '}'
	| ENUM_ ID '{' enumeratorList ',' '}'
	| ENUM_ ID
	;

enumeratorList
	: enumerator
	| enumeratorList ',' enumerator
	;

enumerator
	: ID
	| ID '=' conditionExpr
	;

declarator returns [String name]
	: pointer directDeclarator
	| directDeclarator {
		$name = $directDeclarator.name;
	}
	;

directDeclarator returns [String name]
	: ID {
		$name = $ID.text;
	}
	| '(' declarator ')'
	| directDeclarator '[' typeQuantifierList assignExpr ']' // GNU C99
	| directDeclarator '[' typeQuantifierList ']' // GNU C99
	| directDeclarator '[' assignExpr ']' // GNU C99
	| directDeclarator '[' STATIC_ typeQuantifierList assignExpr ']' // GNU C99
	| directDeclarator '[' typeQuantifierList STATIC_ assignExpr ']' // GNU C99
	| directDeclarator '[' typeQuantifierList '*' ']' // GNU C99
	// | directDeclarator '[' conditionExpr ']' // NOT in GNU C99
	| directDeclarator '[' '*' ']' // GNU C99
	| directDeclarator '[' ']'
	| l1 = directDeclarator '(' {
		System.out.print(" @" + $l1.name + "(");
	} parameterTypeList ')' {
		System.out.println(") #" + attr + " {");
		textCode.add("attributes #" + attr + " = { noinline nounwind optnone sspstrong uwtable \"frame-pointer\"=\"all\" \"min-legal-vector-width\"=\"0\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" }");
		++attr;
	}
	| directDeclarator '(' idList ')'
	| directDeclarator '(' ')'
	;

pointer
	: '*'
	| '*' typeQuantifierList
	| '*' pointer
	| '*' typeQuantifierList pointer
	;

typeQuantifierList
	: typeQuantifier
	| typeQuantifierList typeQuantifier
	;

parameterTypeList
	: parameterList
	| parameterList ',' '...'
	|
	;

parameterList
	: parameterDeclaration
	| parameterList ',' parameterDeclaration
	;

parameterDeclaration
	: declarationSpecifiers declarator
	| declarationSpecifiers abstractDeclarator
	| declarationSpecifiers
	;

idList
	: ID
	| idList ',' ID
	;

typeName
	: specifierQuantifierList
	| specifierQuantifierList abstractDeclarator
	;

abstractDeclarator
	: pointer
	| directAbstractDeclarator
	| pointer directAbstractDeclarator
	;

directAbstractDeclarator
	: '(' abstractDeclarator ')'
	| '[' ']'
	| '[' assignExpr ']' // GNU C99
	// | '[' conditionExpr ']' // NOT in GNU C99
	| directAbstractDeclarator '[' ']'
	| directAbstractDeclarator '[' assignExpr ']' // GNU C99
	// | directAbstractDeclarator '[' conditionExpr ']' // NOT in GNU C99
	| '[' '*' ']' // GNU C99
	| '(' ')'
	| '(' parameterTypeList ')'
	| directAbstractDeclarator '(' ')'
	| directAbstractDeclarator '(' parameterTypeList ')'
	;

initializer returns [Info theInfo] @init { $theInfo = new Info(); }
	: assignExpr {
		$theInfo = $assignExpr.theInfo;
	}
	| '{' initializerList '}'
	| '{' initializerList ',' '}'
	;

// initializerList
// 	: initializer
// 	| initializerList ',' initializer
// 	;

initializerList
	: initializer
	| designation initializer // GNU C99
	| initializerList ',' initializer
	| initializerList ',' designation initializer // GNU C99
	;

designation
	: designatorList '=' // GNU C99
	;

designatorList
	: designator
	| designatorList designator // GNU C99
	;

designator
	: '[' conditionExpr ']'
	| '.' ID // GNU C99
	;

statement
	: labeledStatement
	| exprStatement
	| compoundStatement
	| selectionStatement [labelCnt]
	| iterationStatement 
	| jumpStatement
	;

labeledStatement
	: ID ':' statement
	| CASE_ conditionExpr ':' statement
	| DEFAULT_ ':' statement
	;

// ----- ASCI C -----
// compoundStatement
// 	: '{' '}'
//  	| '{' statementList '}'
//  	| '{' declarationList '}'
//  	| '{' declarationList statementList '}'
// 	;

// statementList
// 	: statement
// 	| statementList statement
// 	;
// ----- ASCI C -----

// ----- GNU C99 -----
compoundStatement
	: '{' '}'
	| '{' blockItemList '}'
	;

blockItemList
	: blockItem
	| blockItemList blockItem
	;

blockItem
	: declaration
	| statement
	;
// ----- GNU C99 -----

exprStatement
	: ';'
	| expr ';'
	;

selectionStatement [int label] @init { ++labelCnt; }
	: IF_ '(' expr ')' {
		Info i = new Info();
		i = $expr.theInfo;

		final String LTrue = "LTrue" + $label;
		final String LExit = "LExit" + $label;
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("br i1 %" + i.theVar.name + ", label %" + LTrue + ", label %" + LExit);
		System.out.println("");
		System.out.println(LTrue + ":");
	} statement {
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("br label %" + LExit);
		System.out.println("");
		System.out.println(LExit + ":");
	}
	| IF_ '(' expr ')' {
		Info i = new Info();
		i = $expr.theInfo;

		final String LTrue = "LTrue" + $label;
		final String LFalse = "LFalse" + $label;
		final String LExit = "LExit" + $label;
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("br i1 %" + i.theVar.name + ", label %" + LTrue + ", label %" + LFalse);
		System.out.println("");
		System.out.println(LTrue + ":");
	} statement ELSE_ {
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("br label %" + LExit);
		System.out.println("");
		System.out.println(LFalse + ":");
	} statement {
		for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
		System.out.println("br label %" + LExit);
		System.out.println("");
		System.out.println(LExit + ":");
	}
	| SWITCH_ '(' expr ')' statement
	;

iterationStatement
	: WHILE_ '(' expr ')' statement
	| DO_ statement WHILE_ '(' expr ')' ';'
	| FOR_ '(' exprStatement exprStatement ')' statement
	| FOR_ '(' exprStatement exprStatement expr ')' statement
	// GNU C99
	| FOR_ '(' declaration exprStatement ')' statement
	// GNU C99
	| FOR_ '(' declaration exprStatement expr ')' statement
	;

jumpStatement
	: GOTO_ ID ';'
	| CONTINUE_ ';'
	| BREAK_ ';'
	| RETURN_ ';'
	| RETURN_ expr ';' {
		if ($expr.theInfo.theVar.name == null && $expr.theInfo.theType == Type.INT) {
			for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
			System.out.println("ret i32 " + $expr.theInfo.theVar.intValue);
		} else if ($expr.theInfo.theVar.name != null) {
			Info i = symtab.get($expr.theInfo.theVar.name);
			if (i == null) {
				System.err.println("RETURN: undefined var: " + i.theVar.name);
			} else if (i.theType == Type.INT) {
				for (int k = 0; k < tabCnt; ++k) System.out.print("\t");
				System.out.println("ret i32 " + i.theVar.intValue);
			}
		}
	}
	;

// ------ Lexer ------

/*----------------------*/
/*   Reserved Keywords  */
/*----------------------*/
ASM_: 'asm';
BREAK_: 'break';
CASE_: 'case';
CHAR_TYPE: 'char';
CONST_TYPE: 'const';
CONTINUE_: 'continue';
DEFAULT_: 'default';
DO_: 'do';
DOUBLE_TYPE: 'double';
ELSE_: 'else';
ENUM_: 'enum';
EXTERN_TYPE: 'extern';
FLOAT_TYPE: 'float';
FOR_: 'for';
GOTO_: 'goto';
IF_: 'if';
INT_TYPE: 'int';
LONG_TYPE: 'long';
PRAGMA_: '#pragma';
REGISTER_: 'register';
RETURN_: 'return';
SHORT_TYPE: 'short';
SIGNED_TYPE: 'signed';
SIZEOF_: 'sizeof';
STATIC_: 'static';
STRUCT_: 'struct';
SWITCH_: 'switch';
TYPEDEF_: 'typedef';
UNION_: 'union';
UNSIGNED_TYPE: 'unsigned';
VOID_TYPE: 'void';
VOLATILE_TYPE: 'volatile';
WHILE_: 'while';

/*----------------------*/
/*   Assign Operators   */
/*----------------------*/
RIGHT_ASSIGN: '>>=';
LEFT_ASSIGN: '<<=';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
MOD_ASSIGN: '%=';
AND_ASSIGN: '&=';
OR_ASSIGN: '|=';
XOR_ASSIGN: '^=';

/*----------------------*/
/*  Compound Operators  */
/*----------------------*/

AND_OP: '&&';
EQ_OP: '==';
LE_OP: '<=';
GE_OP: '>=';
NE_OP: '!=';
INC_OP: '++';
DEC_OP: '--';
OR_OP: '||';
LSHIFT_OP: '<<';
RSHIFT_OP: '>>';
POINTER_OP: '->';

/*----------------------*/
/*   Single Operators   */
/*----------------------*/

ASSIGN_OP: '=';
DIV_OP: '/';
GT_OP: '>';
LT_OP: '<';
MINUS_OP: '-';
MODULO_OP: '%';
NOT_LOGIC_OP: '!';
NOT_BITWISE_OP: '~';
PLUS_OP: '+';
XOR_OP: '^';

COLON: ':';
COMMA: ',';
ASTERK: '*';
SEMICOLON: ';';
DOT: '.';
LEFT_PAREM: '(';
RIGHT_PAREM: ')';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';

/*----------------------*/
/*    Some Functions    */
/*----------------------*/
PRINTF: 'printf';
SCANF: 'scanf';

// fragment LETTER: 'a' .. 'z' | 'A' .. 'Z' | '_'; fragment DIGIT: '0' ..'9';

INCLUDE_: '#include';
INCLUDE_LIB: '<' [a-z/]+ '.h>';
INCLUDE_OWN: '"' [a-z/]+ '.h"';
DEFINE_: '#define';
STRING: '"' ~["\r\n]* '"';
CHAR: '\'' ~['\r\n]* '\'';

ID: [a-zA-Z_][a-zA-Z0-9_]*;
DEC_NUM: [+-]? '0' | [+-]? [1-9][0-9]*;
FLOAT_NUM: [0-9]+ '.' [0-9]* | '.' [0-9]+;

WS: [ \r\n\t]+ -> channel(HIDDEN);
// WS: [ \r\n\t]+ {skip();}; WS: (' ' | '\r' | '\n' | '\t')+ {skip();};
NEW_LINE: '\n'+ {skip();};

/* Comments */
COMMENT1: '//' ~[\r\n]* -> skip;
COMMENT2: '/*' .*? '*/' -> skip;
// COMMENT2: '/*' (options {greedy = false;}: .)* '*/';

// https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// https://gist.github.com/codebrainz/2933703
