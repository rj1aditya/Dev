public class Main {
    public static void main(String[] args) {
        Account a1 = new Account();
        a1.setName("John Doe");
        a1.setAddress("123 Main St");
        a1.setBalance(1000.0);
        a1.setAccountType("Savings");
        System.out.println(a1.calculateInterest());
        Account a2 = new Account();
        a2.setName("Sam Smith");
        a2.setAddress("456 Elm St");
        a2.setBalance(1500.0);
        a2.setAccountType("Checking");
        System.out.println(a2.calculateInterest());
    }
}
