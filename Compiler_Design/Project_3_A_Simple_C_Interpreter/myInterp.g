grammar myInterp;

options {
	language = Java;
}

@header {
    // import packages here. (depends on language)
	import java.util.HashMap;
	import java.util.Stack;
	import java.util.Scanner;
}

@members {  // you can treat it as global variable.
	boolean TRACEON = false;
	final Stack<Boolean> PARSE = new Stack<>();
	HashMap _int = new HashMap();
}

translationUnit:
	externalDeclaration
	| translationUnit externalDeclaration
	| INCLUDE_ (INCLUDE_LIB | INCLUDE_OWN)
	;

externalDeclaration: functionDefinition | declaration;

functionDefinition:
	declarationSpecifiers declarator declarationList compoundStatement
	| declarationSpecifiers declarator compoundStatement;
	// | declarator declarationList compoundStatement // NOT in GNU C99
	// | declarator compoundStatement; // NOT in GNU C99

declarationList: declaration | declarationList declaration;

primaryExpr returns[String a, int val]:
	ID {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $ID.text;
		}
	}
	| DEC_NUM {
		if (PARSE.empty() || PARSE.peek()) {
			$val = Integer.parseInt($DEC_NUM.text);
		}
	}
	| FLOAT_NUM
	| STRING {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $STRING.text;
		}
	}
	| CHAR {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $CHAR.text;
		}
	}
	| '(' expr ')' {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $expr.a;
			$val = $expr.val;
		}
	};

postfixExpr returns[String a, int val]:
	PRINTF '(' STRING ')' {
		if (PARSE.empty() || PARSE.peek()) {
			String str = $STRING.text;
			str = str.replaceAll("\\\\n", "\n");
			str = str.replaceAll("\\\\r", "\r");
			str = str.substring(1, str.length() - 1);
			System.out.print(str);
		}
	}
	| PRINTF '(' STRING COMMA (id=ID | dec=DEC_NUM) ')' {
		if (PARSE.empty() || PARSE.peek()) {
			int val = $dec.text == null ?
				(Integer)_int.get($id.text)
			 	:
				Integer.parseInt($dec.text);
			String str = $STRING.text;
			str = str.replaceAll("\\\\n", "\n");
			str = str.replaceAll("\\\\r", "\r");
			str = str.substring(1, str.length() - 1);
			System.out.printf(str, val);
		}
	}
	| PRINTF '(' STRING COMMA (id1=ID | dec1=DEC_NUM) COMMA (id2=ID | dec2=DEC_NUM) ')' { 
		if (PARSE.empty() || PARSE.peek()) {
			int val1 = $dec1.text == null ?
				(Integer)_int.get($id1.text)
			 	:
				Integer.parseInt($dec1.text);
			int val2 = $dec2.text == null ?
				(Integer)_int.get($id2.text)
			 	:
				Integer.parseInt($dec2.text);

			String str = $STRING.text;
			str = str.replaceAll("\\\\n", "\n");
			str = str.replaceAll("\\\\r", "\r");
			str = str.substring(1, str.length() - 1);
			System.out.printf(str, val1, val2);
		}

	}
	| PRINTF '(' argumentExprList ')' {
		System.err.println("not impl.");
	}
	| SCANF '(' STRING COMMA '&' ID ')' {
		if (PARSE.empty() || PARSE.peek()) {
			var sc = new Scanner(System.in);
			try {
				_int.replace($ID.text, sc.nextInt());
			} catch (Exception e) {
				System.err.println("What the heck?");
			}
		}
	}
	| SCANF '(' STRING COMMA '&' id1=ID COMMA '&' id2=ID ')' {
		if (PARSE.empty() || PARSE.peek()) {
			var sc = new Scanner(System.in);
			try {
				_int.replace($id1.text, sc.nextInt());
				_int.replace($id2.text, sc.nextInt());
			} catch (Exception e) {
				System.err.println("What the heck?");
			}
		}
	}
	| SCANF '(' argumentExprList ')' {	
		System.err.println("not impl.");
	}
	| primaryExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $primaryExpr.a;
			$val = $primaryExpr.val;
		}
	}
	| postfixExpr '[' expr ']'
	| postfixExpr '(' ')'
	| postfixExpr '(' argumentExprList ')'
	| postfixExpr '.' ID
	| postfixExpr POINTER_OP ID
	| postfixExpr INC_OP
	| postfixExpr DEC_OP
	| '(' typeName ')' '{' initializerList '}' // GNU_C99
	| '(' typeName ')' '{' initializerList ',' '}'; // GNU_C99

argumentExprList: assignExpr | argumentExprList ',' assignExpr;

unaryExpr returns[String a, int val]:
	postfixExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $postfixExpr.a;
			$val = $postfixExpr.val;
		}
	}
	| INC_OP unaryExpr // GNU_C99
	| DEC_OP unaryExpr // GNU_C99
	| unaryOP castExpr
	| SIZEOF_ unaryExpr
	| SIZEOF_ '(' typeName ')';

unaryOP: '&' | '*' | '+' | '-' | '~' | '!';

castExpr returns[String a, int val]:
	unaryExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $unaryExpr.a;
			$val = $unaryExpr.val;
		}
	}
	| '(' typeName ')' castExpr;

multiplicativeExpr returns[String a, int val]:
	castExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $castExpr.a;
			$val = $castExpr.val;
		}
	}
	| l1 = multiplicativeExpr '*' r1 = castExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l1.a == null && $r1.a == null) {
				$val = $l1.val * $r1.val;
			} else if ($l1.a == null && $r1.a != null) {
				Integer v = (Integer)_int.get($r1.a);
				if (v != null) {
					$val = $l1.val * v.intValue();
				} else {
					System.err.println("undefined var: " + $r1.a);
				}
			} else if ($l1.a != null && $r1.a == null) {
				Integer v = (Integer)_int.get($l1.a);
				if (v != null) {
					$val = v.intValue() * $r1.val;
				} else {
					System.err.println("undefined var: " + $l1.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l1.a);
				Integer v2 = (Integer)_int.get($r1.a);
				if (v1 == null || v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l1.a);
					} else {
						System.err.println("undefined var: " + $r1.a);
					}
				} else {
					$val = v1.intValue() * v2.intValue();
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l2 = multiplicativeExpr '/' r2 = castExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l2.a == null && $r2.a == null) {
				$val = $l2.val * $r2.val;
			} else if ($l2.a == null && $r2.a != null) {
				Integer v = (Integer)_int.get($r2.a);
				if (v != null) {
					$val = $l2.val / v.intValue();
				} else {
					System.err.println("undefined var: " + $r2.a);
				}
			} else if ($l2.a != null && $r2.a == null) {
				Integer v = (Integer)_int.get($l2.a);
				if (v != null) {
					$val = v.intValue() / $r2.val;
				} else {
					System.err.println("undefined var: " + $l2.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l2.a);
				Integer v2 = (Integer)_int.get($r2.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l2.a);
					} else {
						System.err.println("undefined var: " + $r2.a);
					}
				} else {
					$val = v1.intValue() / v2.intValue();
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l3 = multiplicativeExpr '%' r3 = castExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l3.a == null && $r3.a == null) {
				$val = $l3.val * $r3.val;
			} else if ($l3.a == null && $r3.a != null) {
				Integer v = (Integer)_int.get($r3.a);
				if (v != null) {
					$val = $l3.val * v.intValue();
				} else {
					System.err.println("undefined var: " + $r3.a);
				}
			} else if ($l3.a != null && $r3.a == null) {
				Integer v = (Integer)_int.get($l3.a);
				if (v != null) {
					$val = v.intValue() * $r3.val;
				} else {
					System.err.println("undefined var: " + $l3.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l3.a);
				Integer v2 = (Integer)_int.get($r3.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l3.a);
					} else {
						System.err.println("undefined var: " + $r3.a);
					}
				} else {
					$val = v1.intValue() * v2.intValue();
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	};

additiveExpr returns[String a, int val]:
	multiplicativeExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $multiplicativeExpr.a;
			$val = $multiplicativeExpr.val;
		}
	}
	| l1 = additiveExpr '+' r1 = multiplicativeExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l1.a == null && $r1.a == null) {
				$val = $l1.val + $r1.val;
			} else if ($l1.a == null && $r1.a != null) {
				Integer v = (Integer)_int.get($r1.a);
				if (v != null) {
					$val = $l1.val + v.intValue();
				} else {
					System.err.println("undefined var: " + $r1.a);
				}
			} else if ($l1.a != null && $r1.a == null) {
				Integer v = (Integer)_int.get($l1.a);
				if (v != null) {
					$val = v.intValue() + $r1.val;
				} else {
					System.err.println("undefined var: " + $l1.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l1.a);
				Integer v2 = (Integer)_int.get($r1.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l1.a);
					} else {
						System.err.println("undefined var: " + $r1.a);
					}
				} else {
					$val = v1.intValue() + v2.intValue();
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l2 = additiveExpr '-' r2 = multiplicativeExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l2.a == null && $r2.a == null) {
				$val = $l2.val - $r2.val;
			} else if ($l2.a == null && $r2.a != null) {
				Integer v = (Integer)_int.get($r2.a);
				if (v != null) {
					$val = $l2.val - v.intValue();
				} else {
					System.err.println("undefined var: " + $r2.a);
				}
			} else if ($l2.a != null && $r2.a == null) {
				Integer v = (Integer)_int.get($l2.a);
				if (v != null) {
					$val = v.intValue() - $r2.val;
				} else {
					System.err.println("undefined var: " + $l2.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l2.a);
				Integer v2 = (Integer)_int.get($r2.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l2.a);
					} else {
						System.err.println("undefined var: " + $r2.a);
					}
				} else {
					$val = v1.intValue() - v2.intValue();
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	};

shiftExpr returns[String a, int val]:
	additiveExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $additiveExpr.a;
			$val = $additiveExpr.val;
		}
	}
	| shiftExpr RSHIFT_OP multiplicativeExpr
	| shiftExpr LSHIFT_OP multiplicativeExpr;

relationalExpr returns[String a, int val]:
	shiftExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $shiftExpr.a;
			$val = $shiftExpr.val;
		}
	}
	| l1 = relationalExpr LT_OP r1 = shiftExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l1.a == null && $r1.a == null) {
				if ($l1.val < $r1.val) {
					$val = 1;
				} else {
					$val = 0;
				}
			} else if ($l1.a == null && $r1.a != null) {
				Integer v = (Integer)_int.get($r1.a);
				if (v != null) {
					if ($l1.val < v.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $r1.a);
				}
			} else if ($l1.a != null && $r1.a == null) {
				Integer v = (Integer)_int.get($l1.a);
				if (v != null) {
					if (v.intValue() < $r1.val) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $l1.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l1.a);
				Integer v2 = (Integer)_int.get($r1.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l1.a);
					} else {
						System.err.println("undefined var: " + $r1.a);
					}
				} else {
					if (v1.intValue() < v2.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l2 = relationalExpr GT_OP r2 = shiftExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l2.a == null && $r2.a == null) {
				if ($l2.val > $r2.val) {
					$val = 1;
				} else {
					$val = 0;
				}
			} else if ($l2.a == null && $r2.a != null) {
				Integer v = (Integer)_int.get($r2.a);
				if (v != null) {
					if ($l2.val > v.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $r2.a);
				}
			} else if ($l2.a != null && $r2.a == null) {
				Integer v = (Integer)_int.get($l2.a);
				if (v != null) {
					if (v.intValue() > $r2.val) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $l2.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l2.a);
				Integer v2 = (Integer)_int.get($r2.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l2.a);
					} else {
						System.err.println("undefined var: " + $r2.a);
					}
				} else {
					if (v1.intValue() > v2.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l3 = relationalExpr LE_OP r3 = shiftExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l3.a == null && $r3.a == null) {
				if ($l3.val <= $r3.val) {
					$val = 1;
				} else {
					$val = 0;
				}
			} else if ($l3.a == null && $r3.a != null) {
				Integer v = (Integer)_int.get($r3.a);
				if (v != null) {
					if ($l3.val <= v.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $r3.a);
				}
			} else if ($l3.a != null && $r3.a == null) {
				Integer v = (Integer)_int.get($l3.a);
				if (v != null) {
					if (v.intValue() <= $r3.val) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $l3.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l3.a);
				Integer v2 = (Integer)_int.get($r3.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l3.a);
					} else {
						System.err.println("undefined var: " + $r3.a);
					}
				} else {
					if (v1.intValue() <= v2.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l4 = relationalExpr GE_OP r4 = shiftExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l4.a == null && $r4.a == null) {
				if ($l4.val >= $r4.val) {
					$val = 1;
				} else {
					$val = 0;
				}
			} else if ($l4.a == null && $r4.a != null) {
				Integer v = (Integer)_int.get($r4.a);
				if (v != null) {
					if ($l4.val >= v.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $r4.a);
				}
			} else if ($l4.a != null && $r4.a == null) {
				Integer v = (Integer)_int.get($l4.a);
				if (v != null) {
					if (v.intValue() >= $r4.val) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $l4.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l4.a);
				Integer v2 = (Integer)_int.get($r4.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l4.a);
					} else {
						System.err.println("undefined var: " + $r4.a);
					}
				} else {
					if (v1.intValue() >= v2.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	};

equalityExpr returns[String a, int val]:
	relationalExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $relationalExpr.a;
			$val = $relationalExpr.val;
		}
	}
	| l1 = equalityExpr EQ_OP r1 = relationalExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l1.a == null && $r1.a == null) {
				if ($l1.val == $r1.val) {
					$val = 1;
				} else {
					$val = 0;
				}
			} else if ($l1.a == null && $r1.a != null) {
				Integer v = (Integer)_int.get($r1.a);
				if (v != null) {
					if ($l1.val == v.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $r1.a);
				}
			} else if ($l1.a != null && $r1.a == null) {
				Integer v = (Integer)_int.get($l1.a);
				if (v != null) {
					if (v.intValue() == $r1.val) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $l1.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l1.a);
				Integer v2 = (Integer)_int.get($r1.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l1.a);
					} else {
						System.err.println("undefined var: " + $r1.a);
					}
				} else {
					if (v1.intValue() == v2.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	}
	| l2 = equalityExpr NE_OP r2 = relationalExpr {
		if (PARSE.empty() || PARSE.peek()) {
			if ($l2.a == null && $r2.a == null) {
				if ($l2.val != $r2.val) {
					$val = 1;
				} else {
					$val = 0;
				}
			} else if ($l2.a == null && $r2.a != null) {
				Integer v = (Integer)_int.get($r2.a);
				if (v != null) {
					if ($l2.val != v.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $r2.a);
				}
			} else if ($l2.a != null && $r2.a == null) {
				Integer v = (Integer)_int.get($l2.a);
				if (v != null) {
					if (v.intValue() != $r2.val) {
						$val = 1;
					} else {
						$val = 0;
					}
				} else {
					System.err.println("undefined var: " + $l2.a);
				}
			} else {
				Integer v1 = (Integer)_int.get($l2.a);
				Integer v2 = (Integer)_int.get($r2.a);
				if (v1 == null && v2 == null) {
					if (v1 == null) {
						System.err.println("undefined var: " + $l2.a);
					} else {
						System.err.println("undefined var: " + $r2.a);
					}
				} else {
					if (v1.intValue() != v2.intValue()) {
						$val = 1;
					} else {
						$val = 0;
					}
				}
			}
			$a = "#__rval_"  + RValTemp.next();
			_int.put($a, $val);
		}
	};

andExpr returns[String a, int val]:
	equalityExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $equalityExpr.a;
			$val = $equalityExpr.val;
		}
	}
	| andExpr '&' equalityExpr;

xorExpr returns[String a, int val]:
	andExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $andExpr.a;
			$val = $andExpr.val;
		}
	}
	| xorExpr '^' andExpr;

orExpr returns[String a, int val]:
	xorExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $xorExpr.a;
			$val = $xorExpr.val;
		}
	}
	| orExpr '|' xorExpr;

logicAndExpr returns[String a, int val]:
	orExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $orExpr.a;
			$val = $orExpr.val;
		}
	}
	| logicAndExpr AND_OP orExpr;

logicOrExpr returns[String a, int val]:
	logicAndExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $logicAndExpr.a;
			$val = $logicAndExpr.val;
		}
	}
	| logicOrExpr OR_OP orExpr;

conditionExpr returns[String a, int val]:
	logicOrExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $logicOrExpr.a;
			$val = $logicOrExpr.val;
		}
	}
	| logicOrExpr '?' expr ':' conditionExpr;

assignExpr returns[String a, int val]:
	conditionExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $conditionExpr.a;
			$val = $conditionExpr.val;
			if (TRACEON) {
				Integer v = (Integer)_int.get($a);
				if (v == null) {
					System.out.println("assignExpr get conditionExpr: String: " + $a + " , val: " + $val);
				} else {
					System.out.println("assignExpr get conditionExpr: String: " + $a + " , val: " + v.intValue());
				}
			}
		}
	}
	| unaryExpr assignOP r1 = assignExpr {
		if (PARSE.empty() || PARSE.peek()) {
			Integer v = (Integer)_int.get($unaryExpr.a);
			if (v != null) {
				_int.replace($unaryExpr.a, $r1.val);
				if (TRACEON) {
					System.out.println("assignExpr: " + $unaryExpr.a + ' ' + $assignOP.assign +  ' ' + $r1.val);
				}
			} else {
				System.err.println("undefined var: " + $unaryExpr.a);
			}
		}
	};

assignOP returns[String assign]:
	'=' {
		if (PARSE.empty() || PARSE.peek()) {
			$assign = "=";
		}
	}
	| RIGHT_ASSIGN
	| LEFT_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| AND_ASSIGN
	| OR_ASSIGN
	| XOR_ASSIGN;

expr returns[String a, int val]:
	assignExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $assignExpr.a;
			$val = $assignExpr.val;
		}
	}
	| expr ',' assignExpr;

declaration returns[int val]:
	declarationSpecifiers ';'
	| declarationSpecifiers initDeclaratorList ';' {
		if (PARSE.empty() || PARSE.peek()) {
			$val = $initDeclaratorList.val;
		}
	};

declarationSpecifiers returns[String type]:
	storageClassSpecifier
	| storageClassSpecifier declarationSpecifiers
	| typeSpecifier {
		if (PARSE.empty() || PARSE.peek()) {
			$type = $typeSpecifier.type;
		}
	}
	| typeSpecifier declarationSpecifiers
	| typeQuantifier
	| typeQuantifier declarationSpecifiers;

initDeclaratorList returns[int val]:
	initDeclarator {$val = $initDeclarator.val;}
	| initDeclaratorList ',' initDeclarator;

initDeclarator returns[String dec, int val]:
	declarator {
		if (PARSE.empty() || PARSE.peek()) {
			$dec = $declarator.a;
			$val = 0;
			_int.put($dec, new Integer(0));
			if (TRACEON) {
				System.out.println("initDeclarator: " + $dec + " = 0");
			}
		}
	}
	| l1 = declarator '=' initializer {
		if (PARSE.empty() || PARSE.peek()) {
			$val = $initializer.val;
			$dec = $l1.a;
			if ($initializer.init == null) {
				$val = $initializer.val;
				_int.put($dec, new Integer($val));
				if (TRACEON) {
					System.out.println("initDeclarator: " + $dec + " = " + $val);
				}
			} else {
				Integer v = (Integer)_int.get($initializer.init);
				if (v != null) {
					_int.put($dec, v.intValue());
					if (TRACEON) {
						System.out.println("initDeclarator: " + $dec + " = " + $initializer.init + " = " + $val);
					}
				} else {
					System.err.println("undefined var: " + $initializer.init);
				}
			}
		}
	};

storageClassSpecifier:
	TYPEDEF_
	| EXTERN_TYPE
	| STATIC_
	| REGISTER_;

typeSpecifier returns[String type]:
	VOID_TYPE
	| CHAR_TYPE
	| SHORT_TYPE
	| INT_TYPE {
		if (PARSE.empty() || PARSE.peek()) {
			$type = $INT_TYPE.text;
		}
	}
	| LONG_TYPE
	| FLOAT_TYPE
	| DOUBLE_TYPE
	| SIGNED_TYPE
	| UNSIGNED_TYPE
	| structOrUnionSpecifier
	| enumSpecifier;

typeQuantifier: CONST_TYPE | VOLATILE_TYPE;

structOrUnion: STRUCT_ | UNION_;

structOrUnionSpecifier:
	structOrUnion ID '{' structDeclarationList '}'
	// | structOrUnion ID '{' '}'  // New define
	| structOrUnion '{' structDeclarationList '}'
	| structOrUnion ID;

structDeclarationList:
	structDeclaration
	| structDeclarationList structDeclaration
	|; // New define

structDeclaration:
	specifierQuantifierList structDeclaratorList ';';

specifierQuantifierList:
	typeSpecifier
	| typeSpecifier specifierQuantifierList
	| typeQuantifier
	| typeQuantifier specifierQuantifierList;

structDeclaratorList:
	structDeclarator
	| structDeclaratorList ',' structDeclarator;

structDeclarator:
	declarator
	| ':' conditionExpr
	| declarator ':' conditionExpr;

enumSpecifier:
	ENUM_ '{' enumeratorList '}'
	| ENUM_ ID '{' enumeratorList '}'
	| ENUM_ '{' enumeratorList ',' '}'
	| ENUM_ ID '{' enumeratorList ',' '}'
	| ENUM_ ID;

enumeratorList: enumerator | enumeratorList ',' enumerator;

enumerator: ID | ID '=' conditionExpr;

declarator returns[String a]:
	pointer directDeclarator
	| directDeclarator {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $directDeclarator.a;
		}
	};

directDeclarator returns[String a]:
	ID {
		if (PARSE.empty() || PARSE.peek()) {
			$a = $ID.text;
		}
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
	| directDeclarator '(' parameterTypeList ')'
	| directDeclarator '(' idList ')'
	| directDeclarator '(' ')';

pointer:
	'*'
	| '*' typeQuantifierList
	| '*' pointer
	| '*' typeQuantifierList pointer;

typeQuantifierList:
	typeQuantifier
	| typeQuantifierList typeQuantifier;

parameterTypeList: | parameterList | parameterList ',' '...';

parameterList:
	parameterDeclaration
	| parameterList ',' parameterDeclaration;

parameterDeclaration:
	declarationSpecifiers declarator
	| declarationSpecifiers abstractDeclarator
	| declarationSpecifiers;

idList: ID | idList ',' ID;

typeName:
	specifierQuantifierList
	| specifierQuantifierList abstractDeclarator;

abstractDeclarator:
	pointer
	| directAbstractDeclarator
	| pointer directAbstractDeclarator;

directAbstractDeclarator:
	'(' abstractDeclarator ')'
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
	| directAbstractDeclarator '(' parameterTypeList ')';

initializer returns[String init, int val]:
	assignExpr {
		if (PARSE.empty() || PARSE.peek()) {
			$init = $assignExpr.a;
			$val = $assignExpr.val;
		}
	}
	| '{' initializerList '}'
	| '{' initializerList ',' '}';

// initializerList: initializer | initializerList ',' initializer;

initializerList:
	initializer
	| designation initializer // GNU C99
	| initializerList ',' initializer
	| initializerList ',' designation initializer; // GNU C99

designation: designatorList '='; // GNU C99

designatorList:
	designator
	| designatorList designator; // GNU C99

designator: '[' conditionExpr ']' | '.' ID; // GNU C99

statement returns[String startLabel, String endLabel, String a, int val]:
	labeledStatement
	| exprStatement {$startLabel = Label.next(); $endLabel = Label.next(); }
	| compoundStatement {$startLabel = Label.next(); $endLabel = Label.next(); }
	| selectionStatement {$startLabel = Label.next(); $endLabel = Label.next(); }
	| iterationStatement 
	| jumpStatement;

labeledStatement:
	ID ':' statement
	| CASE_ conditionExpr ':' statement
	| DEFAULT_ ':' statement;

// ----- ASCI C -----
// compoundStatement:
//	'{' '}'
//  | '{' statementList '}'
//  | '{' declarationList '}'
//  | '{' declarationList statementList '}';

// statementList: statement | statementList statement;
// ----- ASCI C -----

// ----- GNU C99 -----
compoundStatement: '{' '}' | '{' blockItemList '}';

blockItemList: blockItem | blockItemList blockItem;

blockItem: declaration | statement;
// ----- GNU C99 -----

exprStatement: ';' | expr ';';

selectionStatement:
	IF_ '(' expr {
		PARSE.push($expr.val != 0 && (PARSE.empty() || PARSE.peek()));
		if (TRACEON) {
			System.out.println("push " + PARSE.peek());
		}
	} ')' statement {
		PARSE.pop();
		if (TRACEON) {
			System.out.println("pop");
		}
	}
	| IF_ '(' expr {
		PARSE.push($expr.val != 0 && (PARSE.empty() || PARSE.peek()));
		if (TRACEON) {
			System.out.println("push " + PARSE.peek());
		}
	} ')' statement ELSE_ {
		boolean last = PARSE.pop();
		PARSE.push(!last && (PARSE.empty() || PARSE.peek()));
		if (TRACEON) {
			System.out.println("modify " + PARSE.peek());
		}
	} statement {
		PARSE.pop();
		if (TRACEON) {
			System.out.println("pop");
		}
	}
	| SWITCH_ '(' expr ')' statement;

iterationStatement:
	WHILE_ '(' expr ')' statement
	| DO_ statement WHILE_ '(' expr ')' ';'
	| FOR_ '(' exprStatement exprStatement ')' statement
	| FOR_ '(' exprStatement exprStatement expr ')' statement
	// GNU C99
	| FOR_ '(' declaration exprStatement ')' statement
	// GNU C99
	| FOR_ '(' declaration exprStatement expr ')' statement;

jumpStatement:
	GOTO_ ID ';'
	| CONTINUE_ ';'
	| BREAK_ ';'
	| RETURN_ ';'
	| RETURN_ expr ';';

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
DEC_NUM: '0' | [1-9][0-9]*;
FLOAT_NUM: [0-9]+ '.' [0-9]* | '.' [0-9]+;

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
RSHIFT_OP: '<<';
LSHIFT_OP: '>>';
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
MULTI_OP_OR_POINTER: '*'+;
SEMICOLON: ';';
DOT: '.';
LEFT_PAREM: '(';
RIGHT_PAREM: ')';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';

WS: [ \r\n\t]+ -> channel(HIDDEN);
// WS: [ \r\n\t]+ {skip();}; WS: (' ' | '\r' | '\n' | '\t')+ {skip();};
NEW_LINE: '\n'+ {skip();};

/* Comments */
COMMENT1: '//' ~[\r\n]* -> skip;
COMMENT2: '/*' .*? '*/' -> skip;
// COMMENT2: '/*' (options {greedy = false;}: .)* '*/';

// https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// https://gist.github.com/codebrainz/2933703
