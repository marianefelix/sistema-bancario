class BankAccount {
    private:
        int userID;
        double balance;

    public:
        BanckAccount(int id, double initialBalance) {
            userID = id;
            balance = initialBalance;
        }

        int getUserID() {
            return userID;
        }

        double getBalance() {
            return balance;
        }
}