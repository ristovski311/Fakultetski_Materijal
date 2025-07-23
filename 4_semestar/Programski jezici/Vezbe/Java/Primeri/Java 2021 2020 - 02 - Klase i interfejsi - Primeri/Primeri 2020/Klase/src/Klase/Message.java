package Klase;
import java.util.Scanner;

public class Message {
    private String text;
    public static int  n = 0;

    public Message() {}

    public void setNewMessage(String t) {
        text = t;
        n++;
    }

    public void showMessage() {
        System.out.println(text);
        System.out.println(n);
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Unesite sadrzaj poruke!");
        String text = scanner.nextLine();
        Message m1 = new Message();
        m1.setNewMessage(text);
        m1.showMessage();
        System.out.println("Unesite sadrzaj poruke!");
        text = scanner.nextLine();
        Message m2 = new Message();
        m2.setNewMessage(text);
        m2.showMessage();
        System.out.println("Unesite sadrzaj poruke!");
        text = scanner.nextLine();
        Message m3 = new Message();
        m3.setNewMessage(text);
        m3.showMessage();
        System.out.println(Message.n);
        scanner.close();
    }
}
