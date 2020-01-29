public class JsonChecker {
    private String json = "";
    private boolean jsonEnd = false;

    public void addString(String s){
        s = tabKiller(s);
        json += s;
        checkJson();
    }

    private void checkJson(){
        int a = 0;
        for(int i = 0; i < json.length(); i++){
            if(json.charAt(i) == '{') a++;
            else if(json.charAt(i) == '}'){
                if(a == 0) throw new IllegalArgumentException(" Wrong Json Format! ");
                a--;
            }
        }
        if((a == 0) && (json.length() > 0)) jsonEnd = true;
        else jsonEnd = false;
    }

    public boolean jsonEnded(){
        return jsonEnd;
    }

    public String getJson() {
        return json;
    }

    public static String tabKiller(String s){
        int l = 0, r = s.length() - 1;
        while((l <= r) && (s.charAt(l) == ' ')){
            l++;
        }
        while((l <= r) && (s.charAt(r) == ' ')){
            r--;
        }
        if(l <= r) return s.substring(l, r + 1);
        return "";
    }
    /*
FOLK
{"mxKolWords":115,"bookName":"123","bookJanr":"FOLK","words":["fkgjdfg","aaa","bb", "tttt"]}
{"mxKolWords":113,"bookName":"123","bookJanr":"CLASSIC","words":["sdgkd","sfgdfs","sg"]}
*/
}
