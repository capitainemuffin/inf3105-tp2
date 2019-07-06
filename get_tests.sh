#!/bin/bash

MoodleSessioncoursv3=d1k76244o60if2100kr8brj124
_shib_uqamidp=1

for i in {1..10}; do 
	curl -o test$i --cookie 'MoodleSessioncoursv3=$MoodleSessioncoursv3;_shib_uqamidp=$_shib_uqamidp' https://www.moodle2.uqam.ca/coursv3/pluginfile.php/2991819/mod_folder/content/0/test$i.txt?forcedownload=1
	curl -o test$ires --cookie 'MoodleSessioncoursv3=$MoodleSessioncoursv3;_shib_uqamidp=$_shib_uqamidp' https://www.moodle2.uqam.ca/coursv3/pluginfile.php/2991819/mod_folder/content/0/test$ires.txt?forcedownload=1
done

if  [ ! -d tests ]; then mkdir tests; fi 
mv test[^s]* tests
rm test

echo 'done';