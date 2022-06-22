
// class used to initiate each bingo square. 
// Assigns words from list of phrases and a corresponding score.
class BingoSquare {
    
    // a static list of phrases that will be used to fill the bingo board
    static bingoWords = [
        { words: "quote from civil rights leader", score: 10, used: false },
        { words: "quote from children's book", score: 10, used: false },
        { words: "quote from movie/song", score: 10, used: false },
        { words: "quote from a poet", score: 10, used: false },
        { words: "someone trips", score: 10, used: false },
        { words: "peace sign", score: 10, used: false },
        { words: "speech about tragedy", score: 10, used: false },
        { words: "crying baby", score: 10, used: false },
        { words: "sign/shirt with grad's photo", score: 10, used: false },
        { words: "bundle of balloons", score: 10, used: false },
        { words: "first day of the rest of your lives", score: 10, used: false },
        { words: "never stop learning", score: 10, used: false },
        { words: "travel/journey metaphor", score: 10, used: false },
        { words: "definition from dictionary", score: 10, used: false },
        { words: "thanks family", score: 10, used: false },
        { words: "class of XXXX", score: 10, used: false },
        { words: "mispronounced name", score: 10, used: false },
        { words: "someone yells a nickname", score: 10, used: false },
        { words: "rehearsed group scream", score: 10, used: false },
        { words: "clapping goes on too long", score: 10, used: false },
        { words: "sequins/glitter", score: 10, used: false },
        { words: "dance, dab or strut on stage", score: 10, used: false },
        { words: "sports analogy", score: 10, used: false },
        { words: "crying", score: 10, used: false },
        { words: "hugs person giving out diploma", score: 10, used: false },
        { words: "super high heels", score: 10, used: false },
        { words: "future", score: 10, used: false },
        { words: "obstacle", score: 10, used: false },
        { words: "challenge", score: 10, used: false },
        { words: "dreams", score: 10, used: false },
        { words: "heart", score: 10, used: false },
        { words: "dreams", score: 10, used: false },
        { words: "chapter", score: 10, used: false },
        { words: "secret", score: 10, used: false },
        { words: "no one laughs at joke", score: 10, used: false },
        { words: "Someone playing a video game", score: 10, used: false },
        { words: "phone rings", score: 10, used: false },
        { words: "school mascot mentioned", score: 10, used: false },
        { words: "social media mentioned", score: 10, used: false },
        { words: "someone's name ends with III or higher", score: 10, used: false },
        { words: "someone yells bingo", score: 10, used: false }
      ];
    
    // assigns a random phrase and then deletes that phrase from the list of possible phrases
    // there must be more phrases than the number of bingo squares in the game
    constructor() {
        this.clicked = false;
        let randomWordsNumber = Math.floor(Math.random() * BingoSquare.bingoWords.length); // get random number for the words to be used
        this.words = BingoSquare.bingoWords[randomWordsNumber].words; // assign random words to this square
        this.score = BingoSquare.bingoWords[randomWordsNumber].score; // assign score to this square
        BingoSquare.bingoWords.splice(randomWordsNumber, 1); // delete that random words from the words array so they can't be used again
    }

    //unused
    bingoClickExampleMethod() {
        this.clicked = true;
    }
}



// object to represent the bingo game
var bingo = {

    bingoScore : 0, // the score of the player
    horizontalSpaces : 3, // number of horizontal spaces on the bingo card
    verticalSpaces : 5, // number of vertical spaces on the bingo card
    bingoBoard : new Array (this.horizontalSpaces), // an array of arrays to store the words, scores and whether each square has been clicked
    
    // initializes the bingo board
    start : function() {
        
        // create arrays
        for ( let i = 0; i < this.horizontalSpaces; i++ ) {
            this.bingoBoard[i] = new Array (this.verticalSpaces);
        }

        // initialize the bingo squares
        for ( let i=0; i < this.horizontalSpaces; i++ ) {
            for ( let j=0; j < this.verticalSpaces; j++ ) {
                this.bingoBoard[i][j] = new BingoSquare();
            }
        }  
        
        this.printToConsole();
        // if horizontal and vertical spaces are odd, set free space on center space


    },

    clickSquare : function () {

    },

    checkHorizontal : function() {
        
    },

    checkVertical : function() {
        
    },

    checkDiagonal : function() {
        
    },


    getScore : function() {
        
    },

    printToConsole : function () {
        for ( let i=0; i < this.horizontalSpaces; i++ ) {
            for ( let j=0; j < this.verticalSpaces; j++ ) {
                console.log(i + " " + j + " " + this.bingoBoard[i][j].words);
            }
        }  
    }

}



window.addEventListener('load', (event) => {
    console.log('The page has fully loaded');
    bingo.start();
});


