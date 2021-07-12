package forms;

import java.io.IOException;

public class ProtectedFormMain {
    public static void main(String[] args) throws IOException {
        Form enrollForm = new Form();
        Field<Integer> age = new Field<Integer>(s -> Integer.valueOf(s)).
            addValidation(a -> a > 18, "value should be bigger than 18").
            addValidation(a -> a < 66, "value should be less than 66"); Field<Boolean> yesNo = new Field<>(s -> s.toUpperCase().equals("YES"));
        enrollForm.add("What is your age?", age). add("Are you married?", yesNo);
        
        AbstractForm pf = ProtectedForm.protect(enrollForm, "qwerty");
        
        System.out.println(pf.exec());
        System.out.println(pf.exec());
    }
}
