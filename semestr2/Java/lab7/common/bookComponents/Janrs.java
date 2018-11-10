package common.bookComponents;

public enum Janrs {
    EZOTERIC, CLASSIC, FOLK;

    @Override
    public String toString() {
        return "Janrs{}";
    }

    public static boolean checkJanr(String janr){
        if(janr == null) return false;
        try {
            Janrs jan = Janrs.valueOf(janr);
        }
        catch (Exception e) {
            return false;
        }
        return true;
    }

    public static String[] getJanrs(){
        Janrs janrs[] = Janrs.values();
        String stringJanrs[] = new String[janrs.length];
        for(int i = 0; i < janrs.length; i++){
            stringJanrs[i] = janrs[i].name();
        }
        return stringJanrs;
    }

}

