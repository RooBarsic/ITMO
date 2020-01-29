import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.faces.component.UIComponent;
import javax.faces.application.FacesMessage;

import javax.faces.context.FacesContext;

import javax.faces.validator.Validator;
import javax.faces.validator.FacesValidator;
import javax.faces.validator.ValidatorException;

@FacesValidator("ValidatorR")
public class ValidatorR implements Validator{

    @Override
    public void validate(FacesContext facesContext, UIComponent uiComponent, Object o) throws ValidatorException {
        System.out.println(" ---- Somebody ask My Validator ");

        int x = 24;
    }
}
