val=123
sum=0
while [ $val -ne 0 ]
do
	temp=$((val%10))
	sum=$((sum+temp))
	val=$((val/10))
done

echo $sum
