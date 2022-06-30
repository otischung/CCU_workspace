import re

number = 0
total = 0
pattern = re.compile("[^\d\+\-]")
while True:
    print("Please input your score:")
    line = input()
    result = pattern.search(line)
    if result is not None:
        print("illegal input, ending the program...", flush=True)
        quit(1)
    try:
        grade = float(line)
    except ValueError:
        grade = 0
        print("illegal input, ending the program...")
        quit(1)
    if grade == -1:
        break
    elif grade < 0 or grade > 100:
        print("illegal input, ending the program...", flush=True)
        quit(1)
    else:
        total += grade
        number += 1

average = total / number
print(f"The average is {average:.2f}.")
