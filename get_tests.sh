#!/bin/bash

_shib_uqamidp=1

for i in {1..10}; do 
	curl -o test$i --cookie "MoodleSessioncoursv3=$1;_shib_uqamidp=$_shib_uqamidp" https://www.moodle2.uqam.ca/coursv3/pluginfile.php/2991819/mod_folder/content/0/test$i.txt?forcedownload=1
	curl -o test"$i"res --cookie "MoodleSessioncoursv3=$1;_shib_uqamidp=$_shib_uqamidp" https://www.moodle2.uqam.ca/coursv3/pluginfile.php/2991819/mod_folder/content/0/test"$i"res.txt?forcedownload=1
done

if  [ ! -d tests ]; then mkdir tests; fi 
	
mv test[^s]* tests
echo 'done';