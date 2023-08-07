for c in $(cat candidates.txt | cut -d ' ' -f 2-3 | tr -s ' ' ',' | tr -s ',');do
	v=$(echo $c | sed -E 's/(.*),(.*)/\1, \2/g')
	w=$(cat declarations.txt | grep "$v"|  wc -l)
	echo "$v a $w votes"
done
