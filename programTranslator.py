import sys

filename = sys.argv[1]

f = open(filename)

instructions = {
	"ldi": "00000001",
	"addi": "00000010",
	"halt": "00000101"
}

def to_binary(num, res):
	if num >=1:
		to_binary(num // 2, res)
	res += str(num % 2)

z = open('./' + filename + '.binary', 'w')

line = f.readline()

while not line.__contains__('.end'):
	for i in instructions:
		rhs = ""
		if line.__contains__(i):
			z.write(instructions[i])
			# if there's a space there's a constant to grab
			if line.__contains__(' '):
				constant = format(int(line[len(i)+1:len(line)-1]), '08b')
				z.write(constant)
			else:
				z.write("00000000")
			z.write('\n')
	line = f.readline()




f.close()