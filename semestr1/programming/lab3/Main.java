public class Main {
    public static void main(String[] args){
        System.out.println("Hello Barsic");
        //*
        ClassicUniver univerX = new ClassicUniver("Marvel", 150, "MarvelComics");
        String[] words = {  "черная бездна",
                "резные края",
                "протошогготы",
                "пятимерные, наглухо закрытые конструкции",
                "мерзкий цилиндр",
                "древний Фарос",
                "Иог-Сотот",
                "исходная белая студнеобразная структура",
                "космический оттенок",
                "крылья",
                "глаза в темноте",
                "лунная дорожка",
                "первозданный",
                "вечный, неумирающий"   };
        Janrs goldenJan = Janrs.Ezoteric;
        Book boo = new Book("Nekromikon", goldenJan,14, words);
        Keys goldenKey = Keys.Lola;
        univerX.addNewBookB(boo, goldenKey);
        Man deni = new Man("Denfort");
        deni.ifoundKeyX(Keys.goldenKey);
        if((univerX.haveBookBJ("Nekromikon", goldenJan)) &&
                (univerX.checkKeyForBookBJ("Nekromikon", goldenJan, deni.getManKey())) == true)
            deni.read(univerX.getBookFromLibrary("Nekromikon", goldenJan, deni.getManKey()));
        deni.transActive();
       // deni.getWordInfo();
        //*/
        System.out.println("Bye Barsic");
    }
}
