#! /bin/bash

for i
do
	up=${i^^}
	premiere_lettre=${i:0:1}
	premiere_lettre_majuscule=${premiere_lettre^^}
	cap="$premiere_lettre_majuscule""${i:1}"

	if [ -f $cap.h ] || [ -f $cap.cpp ]; then
		echo "Files $cap.{h, cpp} already exist, not touch"
		continue
	fi
 
	echo "Files $cap.{h, cpp} don't exist, creation ..."

	touch "$cap".cpp
	touch "$cap".hpp
		
	echo "\
#ifndef __"$up"_H__
#define __"$up"_H__


class "$cap" {
	protected:
	public:
		"$cap"();
		~"$cap"();
};


#endif
" > "$cap".hpp
	
	echo "\
#include \"$cap.hpp\"
" > "$cap".cpp

done
