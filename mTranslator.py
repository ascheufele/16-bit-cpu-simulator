f = open("./macrocode.txt", "r")
macrocode = f.read()
f.close()

macrocode = macrocode.split('\n')

first_pass = []

# first pass
for i in range(len(macrocode)-1):
	if macrocode[i][0] != '#' and macrocode[i][0] != '\n':
		first_pass.append(macrocode[i][3:len(macrocode[i])-1])

print(first_pass)

f = open("./microcode.txt", "w")

# second pass
defs = ['pc incr', 'ram in', 'ram out', 'a in', 'a out', 'ir in', 'reset', 'b in', 'alu out', 'halt']

for i in range(len(first_pass)):
	code = first_pass[i]
	instruction = list("0000000000\n")
	for j in range(len(defs)):
		if code.__contains__(defs[j]):
			instruction[j] = '1'
	f.write(''.join(instruction))


f.close()
