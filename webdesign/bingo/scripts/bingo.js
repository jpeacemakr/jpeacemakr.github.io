
// class used to initiate each bingo square. 
// Assigns words from list of phrases and a corresponding score.
class BingoSquare {
    
    // a static list of phrases that will be used to fill the bingo board
    static bingoWords = [
        { words: "Quote from <br>civil rights leader", score: 10, used: false },
        { words: "Quote from <br>children's book", score: 10, used: false },
        { words: "Quote from <br>movie/song", score: 10, used: false },
        { words: "Quote <br>from <br>a poet", score: 10, used: false },
        { words: "Someone <br>trips", score: 10, used: false },
        { words: "Peace <br>sign", score: 10, used: false },
        { words: "Speech <br>about <br>tragedy", score: 10, used: false },
        { words: "Crying <br>baby", score: 10, used: false },
        { words: "Sign/shirt <br>with grad's <br>photo", score: 10, used: false },
        { words: "Bundle of <br>balloons", score: 10, used: false },
        { words: "First day <br>of the rest <br>of your lives", score: 10, used: false },
        { words: "Never <br>stop <br>learning", score: 10, used: false },
        { words: "Travel/journey <br>metaphor", score: 10, used: false },
        { words: "Definition <br>from <br>dictionary", score: 10, used: false },
        { words: "Thanks <br>family", score: 10, used: false },
        { words: "Class of <br>XXXX", score: 10, used: false },
        { words: "Name <br>pronounced <br>wrong", score: 10, used: false },
        { words: "Someone <br>yells a <br>nickname", score: 10, used: false },
        { words: "Rehearsed <br>group <br>scream", score: 10, used: false },
        { words: "Clapping <br>goes on <br>too long", score: 10, used: false },
        { words: "Sequins/<br>glitter", score: 10, used: false },
        { words: "Dance, <br>dab or strut <br>on stage", score: 10, used: false },
        { words: "Sports <br>analogy", score: 10, used: false },
        { words: "Crying", score: 10, used: false },
        { words: "Hugs person <br>giving out \ndiploma", score: 10, used: false },
        { words: "Super <br>high <br>heels", score: 10, used: false },
        { words: "'future'", score: 10, used: false },
        { words: "'obstacle'", score: 10, used: false },
        { words: "'challenge'", score: 10, used: false },
        { words: "'dreams'", score: 10, used: false },
        { words: "'heart'", score: 10, used: false },
        { words: "'dreams'", score: 10, used: false },
        { words: "'chapter'", score: 10, used: false },
        { words: "'secret'", score: 10, used: false },
        { words: "No one <br>laughs at <br>joke", score: 10, used: false },
        { words: "Someone <br>playing a <br>video game", score: 10, used: false },
        { words: "Phone <br>rings", score: 10, used: false },
        { words: "School <br>mascot <br>mentioned", score: 10, used: false },
        { words: "Social <br>media <br>mentioned", score: 10, used: false },
        { words: "Someone's <br>name ends <br>with III <br>or higher", score: 10, used: false },
        { words: "Someone <br>yells <br>bingo", score: 10, used: false }
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
                // replace static content with randomly generated phrases
                if (i!==1 || j!==2){
                    $("#square" + (i+1) + (j+1) + "-inside").children("p").html(this.bingoBoard[i][j].words);
                }
            }
        }  
        this.printToConsole();
    },

    clickSquare : function (square) {
        console.log("running bingo.clickSquare");
        // if square doesn't have class big, add it. else if it does, remove it
        if($(square).hasClass("big")) {
            $(square).removeClass("big");
            if($(square).hasClass("picked")) {
                $(square).removeClass("picked");
                // remove score
                //console.log($(square).attr("id").charAt(6)-1);
                //console.log($(square).attr("id").charAt(7)-1);
                this.bingoBoard[$(square).attr("id").charAt(6)-1][$(square).attr("id").charAt(7)-1].picked = false;
            }
            else { 
                $(square).addClass("picked");
                // add score string
                //console.log($(square).attr("id").charAt(6)-1);
                //console.log($(square).attr("id").charAt(7)-1);
                this.bingoBoard[$(square).attr("id").charAt(6)-1][$(square).attr("id").charAt(7)-1].picked = true;
            }
        } else {
            $(square).addClass("big");
        }
    },

    checkHorizontal : function() {
        
    },

    checkVertical : function() {
        
    },

    checkDiagonal : function() {
        
    },


    getScore : function() {
        bingoScore = 0;
        for ( let i=0; i < this.horizontalSpaces; i++ ) {
            for ( let j=0; j < this.verticalSpaces; j++ ) {
                if (this.bingoBoard[i][j].picked === true) {
                    bingoScore = bingoScore + this.bingoBoard[i][j].score;
                }
            }
        }
        // console.log("Score:" + bingoScore);
        $(".score").html("Your score is: " + bingoScore);
  
    },

    printToConsole : function () {
        for ( let i=0; i < this.horizontalSpaces; i++ ) {
            for ( let j=0; j < this.verticalSpaces; j++ ) {
                console.log(i + " " + j + " " + this.bingoBoard[i][j].words);
            }
        }  
    }

}


$(document).ready(function(){
    //console.log("ready");

    // initialize the game board with random phrases
    bingo.start();

    // make square big and calculate score when you click on it
    $(".square-inside").click(function(){
      //console.log("click");
      bingo.clickSquare(this);
      bingo.getScore();
    });

  });




