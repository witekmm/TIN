package client.Utils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class IPValidator {

    private Pattern pattern;

    private static final String IPADDRESS_PATTERN =
            "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                    "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                    "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                    "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$";

    public IPValidator(){
        pattern = Pattern.compile(IPADDRESS_PATTERN);
    }

    public boolean validate(final String ipAddress){
        Matcher matcher = pattern.matcher(ipAddress);
        return matcher.matches();
    }
}
