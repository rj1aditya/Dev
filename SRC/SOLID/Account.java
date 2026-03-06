public class Account {
    public String userName;
    public String userAddress;
    public double userBalance;
    public String userAccountType;

    public String getName() {
        return userName;
    }

    public void setName(String name) {
        userName = name;
    }

    public String getAddress() {
        return userAddress;
    }

    public void setAddress(String address) {
        userAddress = address;
    }

    public double getBalance() {
        return userBalance;
    }

    public void setBalance(double balance) {
        userBalance = balance;
    }

    public String getAccountType() {
        return userAccountType;
    }

    public void setAccountType(String accountType) {
        userAccountType = accountType;
    }

    public double calculateInterest() {
        if (userAccountType.equals("Savings")) {
            return userBalance * 0.04;
        } else {
            return userBalance * 0.02;
        }
    }
};