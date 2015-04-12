from os.path import exists

print "Type the filename :" 
file= raw_input("> ") 
if exists(file): 
	txt_again = open(file,'r') 
	print txt_again.read() 
else: 
	print "no such file"... 
print "Type the filename "

filename = raw_input("> ")

print "We're going to erase %r." % filename

print "Opening the file..."

'''this will open the file if it is exist if file does not exist it will create new file''' 
target = open(filename, 'w')
'''we will truncate data of file if file is already exist''' 
print "Truncating the file." target.truncate()

print "Write three lines."

line1 = raw_input("line 1: ") 
line2 = raw_input("line 2: ") 
line3 = raw_input("line 3: ")

print "We are going to write these to the file."

target.write(line1) 
target.write("\n") 
target.write(line2) 
target.write("\n") 
target.write(line3) 
target.write("\n")

print "And finally, we close it." 
target.close().
