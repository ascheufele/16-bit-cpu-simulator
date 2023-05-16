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
# if this changes it also must be updated in control_logic.hpp
# C_IN, C_OUT, D_IN, D_OUT, E_IN, E_OUT, F_IN, F_OUT, ADD, SUB, LSH, RSH
defs = ['pc incr', 'ram in', 'ram out', 'a in', 'a out', 'ir in', 'reset', 'b in', 'alu out', 'halt', 'pc inp',
		'c in', 'c out', 'd in', 'd out', 'e in', 'e out', 'f in', 'f out', 'add', 'sub', 'lsh', 'rsh']

for i in range(len(first_pass)):
	code = first_pass[i]
	instruction = list("00000000000000000000000\n")		# must be updated when the microcode width changes. I'm going to look into using a DLL for this'
	for j in range(len(defs)):
		if code.__contains__(defs[j]):
			instruction[j] = '1'
	f.write(''.join(instruction))


f.close()
