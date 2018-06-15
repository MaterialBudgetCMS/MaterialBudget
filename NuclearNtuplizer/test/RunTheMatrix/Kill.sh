i=$1
j=$2

echo $i $j

while [ $i -le $j ]; do
bkill $i
i=$[i+1]
done