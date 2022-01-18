
import java.util.Scanner;

/**
 * Exit objects represent a connection between two {@link Room} objects. Each {@link Room} 
 * can have many exits, but each Exit only has a source Room, and a destination Room. Exits 
 * are referenced by their associated direction, and are designed to move the user from one
 * Room to another by inputting the direction of the exit.
 *
 * Note that Exits can only be traversed in one direction, meaning two exits are required 
 * to make two rooms where the user can move back and forth between them. 
 *
 * @author Michael Goyer
 */
public class Exit {

    class NoExitException extends Exception {}

    private String dir;
    private Room src, dest;

    /**
     * Exit constructor for non-hydrated exits. 
     * @param dir A string representing the direction of the Exit. 
     * @param src The name of the exit's source Room.
     * @param dest The name of the exit's destination Room.
     */
    Exit(String dir, Room src, Room dest) {
        init();
        this.dir = dir;
        this.src = src;
        this.dest = dest;
        src.addExit(this);
    }

    /** Given a Scanner object positioned at the beginning of an "exit" file
        entry, read and return an Exit object representing it. 
        @param d The dungeon that contains this exit (so that Room objects 
        may be obtained.)
        @throws NoExitException The reader object is not positioned at the
        start of an exit entry. A side effect of this is the reader's cursor
        is now positioned one line past where it was.
        @throws IllegalDungeonFormatException A structural problem with the
        dungeon file itself, detected when trying to read this room.
     */
    Exit(Scanner s, Dungeon d) throws NoExitException,
        Dungeon.IllegalDungeonFormatException {

        init();
        String srcTitle = s.nextLine();
        if (srcTitle.equals(Dungeon.TOP_LEVEL_DELIM)) {
            throw new NoExitException();
        }
        src = d.getRoom(srcTitle);
        dir = s.nextLine();
        dest = d.getRoom(s.nextLine());
        
        // I'm an Exit object. Add me as an exit to my source Room.
        src.addExit(this);

        // throw away delimiter
        if (!s.nextLine().equals(Dungeon.SECOND_LEVEL_DELIM)) {
            throw new Dungeon.IllegalDungeonFormatException("No '" +
                Dungeon.SECOND_LEVEL_DELIM + "' after exit.");
        }
    }

    // Common object initialization tasks.
    private void init() {
    }

    /**
     * Returns a string containing the direction of the Exit, as well as it's destination Room. The 
     * destination room is the room to which the exit leads. 
     */
    String describe() {
        return "You can go " + dir + " to " + dest.getTitle() + ".";
    }

    /**
     * Returns a string containing the exit's direction. Valid directions are n, s, e, w, u, d (meant
     * to represent north, south, east, west, up and down respectively).
     */
    String getDir() { return dir; }

    /**
     * Returns the exit's source Room. The source room is the room from which the exit comes.
     */
    Room getSrc() { return src; }

    /**
     * Returns the exit's destination Room. The destination room is the room to which an exit leads. 
     */
    Room getDest() { return dest; }
}
