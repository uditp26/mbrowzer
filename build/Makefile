# -*- Makefile -*-

# Source directory path
src := ../src/
src_dom := ${src}dom/
src_html := ${src}html/

# Include directory path
inc := ../include/
inc_dom := ${inc}dom/
inc_html := ${inc}html/

# Object directory path
obj_path := obj/

# objects
objects := ${obj_path}main.o ${obj_path}parser.o ${obj_path}text.o ${obj_path}element.o ${obj_path}node.o 

all : main.exe

main.exe : ${objects}
		g++ ${objects} -o main.exe -g

${obj_path}main.o : ${src}main.cpp
		g++ -c ${src}main.cpp -o ${obj_path}main.o -g

${obj_path}parser.o : ${src_html}Parser.cpp ${inc_html}Parser.h
		g++ -c ${src_html}Parser.cpp -o ${obj_path}parser.o -g

${obj_path}text.o : ${src_dom}Text.cpp ${inc_dom}Text.h
		g++ -c ${src_dom}Text.cpp -o ${obj_path}text.o -g

${obj_path}element.o : ${src_dom}Element.cpp ${inc_dom}Element.h
		g++ -c ${src_dom}Element.cpp -o ${obj_path}element.o -g

${obj_path}node.o : ${src_dom}Node.cpp ${inc_dom}Node.h
		g++ -c ${src_dom}Node.cpp -o ${obj_path}node.o -g