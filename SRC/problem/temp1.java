import java.util.*;

class class {
public static void main (String[] args) {
Scanner scn = new Scanner(System.in);
int n = scn.nextInt();
int m = scn.nextInt();
int a[] = new int[n];
for(int i=0;i<n;i++){
a[i] = scn.nextInt();
}
int count =0;
for(int i =0;i<n;i++){
int total =0;
for(int j =i; j<n;j++){
total += a[i];
if(total<= m){
count = Math.max(count , ((j-i)+1));
}
}
}
System.out.println(count);
}
}