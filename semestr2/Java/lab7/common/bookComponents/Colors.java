package common.bookComponents;

import java.awt.*;

public enum Colors {
    RED, BLUE, BLACK, GREEN;

    @Override
    public String toString() {
        return "Janrs{}";
    }

    public static boolean checkColor(String color){
        if(color == null) return false;
        try {
            Colors colo = Colors.valueOf(color);
        }
        catch (Exception e) {
            return false;
        }
        return true;
    }

    public static String[] getColors(){
        Colors colors[] = Colors.values();
        String stringColors[] = new String[colors.length];
        for(int i = 0; i < colors.length; i++){
            stringColors[i] = colors[i].name();
        }
        return stringColors;
    }

    public static Color getColor(Colors color, int idVis){
        switch (color.name()){
            case "BLUE": return new Color(0, 0, 255, idVis);
            case "GREEN": return new Color(0, 255, 0, idVis);
            case "RED": return new Color(255, 0, 0, idVis);
            case "BLACK": return new Color(0, 0, 0, idVis);
            default: return null;
        }
    }
}
