package сlient;

import common.bookComponents.Book;

import java.io.Serializable;

public class ClientOwl implements Serializable {
    private String message;

    public ClientOwl(String message) {
        this.message = message;
    }

    public String getMessage() {
        return message;
    }
}