 // json data retrieved from weather service
 let positionResult; // stores location json info
 let weatherResult; // stores daily weather forecast json info
 let weatherResultHourly; // stores hourly weather forecast json info

 // arrays to store images for each day of the week. Typically 0..7 or 0..8
 let weatherImageArray = [];

 // use weather information to get what dolly says
 // day is day of week 0-X that image will be assigned to
 // position is position of data (0-13) from weather service API. 
 // num is number of positions to include (1 for half day or 2 for full day)
 function dollySays(day, position, num) {
 
   let dollyWords = ""; // the string that will be built
   let dollyWordsObject; // object to be assigned { words:"xxx", image:"xxx", position:"xxxx" }. 
                         // it will store the last object (image and position to be used) as the string is being built.
                         // this setup allows an image and position to be linked with a specific phrase
                         // the array of phrase objects allows one of the phrases to be randomly chosen for a particular weather type
     
   // level of sunshine
   const clearWords = [
     { words: " It would be good night to chase opossums!", image: "night.jpg", position: "bottom center" }, 
     { words: " Maybe I will see the sky ball tonight.", image: "night.jpg", position: "bottom center" },
     { words: " Maybe the raccoon will visit my trash tonight (That's where the no-no food goes).", image: "night.jpg", position: "bottom center" }

   ];
   const sunWords = [
     { words: " Today would be good day for a cheeseburger party in the backyard.", image: "cookout4.jpg", position: "center right" },
     { words: " It will be bright today.", image: "sun1.jpg", position: "bottom center" },
     { words: " Today will be a good day to lie in the sun.", image: "grass.jpg", position: "top right" },
     { words: " The sun can warm my belly today. Not as good as chicken warms my belly, but good enough.", image: "grass.jpg", position: "top right" },
     { words: " Sun's out, tongues out!", image: "bench.jpg", position: "top left" }

   ];
   const mostSunWords = [
     { words: " There will only be a few sky fluffs in the air today.", image: "mostsunny1.jpg", position: "center center" }

   ];
   const partSunWords = [
     { words: " There will some sky fluffs in the air today.", image: "sunset.jpg", position: "center right" },
     { words: " Would be a good day to drive to Dairy Queen? I sit in backseat and wait for cheeseburger.", image: "drive.jpg", position: "center center" }

   ];
   const partCloudWords = [
     { words: " There will be some sky fluffs in the air today.", image: "partcloudy1.jpg", position: "top right" },
     { words: " It would be good day to watch the sunset on the bench with Papa.", image: "partcloudy2.jpg", position: "top right" }

   ];
   const mostCloudWords = [
     { words: " There will be a lot of sky fluffs in the air today.", image: "sunset.jpg", position: "center right" }

   ];
   const cloudWords = [
     { words: " The sky fluffs will fill the air today.", image: "sunset.jpg", position: "center right" }

   ];

   // temperature
   const hotWords = [
     { words: " It will be so hot. Bring water bowl on your walk.", image: "grass.jpg", position: "top right" },
     { words: " Keep paws off the outdoor floor so they don't get burned.", image: "corner.jpg", position: "bottom left" },
     { words: " It is hot. Can I has trip to the pool too?", image: "drive.jpg", position: "center center" },
     { words: " So hot. It would be good day for ice cream cone. Peanut butter is my favorite, not doggo cone!", image: "cone2.jpg", position: "top center" },
     { words: " When I go outside, I has the pants!", image: "bench.jpg", position: "top left" }

   ];
   const warmWords = [
     { words: " It will be so hot. Bring water bowl on your walk.", image: "sun1.jpg", position: "center center" },
     { words: " Keep paws off the outdoor floor so they don't get burned.", image: "corner.jpg", position: "bottom right" },
     { words: " Can I has trip to the pool too?", image: "drive.jpg", position: "center center" },
     { words: " It would be good day for ice cream cone. Peanut butter is my favorite, not doggo cone!", image: "cone2.jpg", position: "top center" },
     { words: " When I go outside, I has the pants!", image: "bench.jpg", position: "top left" }

   ];
   const coolWords = [
     { words: " It will be so cold that I need my extra fur.", image: "night.jpg", position: "bottom center" },
     { words: " I found this leaf on my walk. I thought it was banana. It does not taste like banana but I carry it home anyways.", image: "banana.jpg", position: "center left" },
     { words: " It will be cold, but nice hot chicken could keep me warm.", image: "night.jpg", position: "bottom center" }

   ];
   const coldWords = [
     { words: " It will be so cold that I need my extra fur.", image: "night.jpg", position: "bottom center" },
     { words: " It will be cold, but nice hot chicken could keep me warm.", image: "night.jpg", position: "bottom center" }

   ];
   
   // precipitation
   const chanceRainWords = [ 
     { words: " The sky fluffs might be drooling.", image: "rain2.jpg", position: "top right" }, 
     { words: " I might brings in the mud from the walk.", image: "rain3.jpg", position: "top right" },
     { words: " It might be a good day for couch cuddles if too wet for walks.", image: "couch2.jpg", position: "top right" },
     { words: " Outside might be like bath time.", image: "rain3.jpg", position: "top right" }

   ];
   const rainWords = [ 
     { words: " The sky fluffs will be drooling.", image: "rain2.jpg", position: "top right" }, 
     { words: " I will bring in the mud from the walk.", image: "rain1.jpg", position: "top right" },
     { words: " Rain makes it a good day for couch cuddles.", image: "ferocious.jpg", position: "center right" },
     { words: " Outside will be like bath time.", image: "rain3.jpg", position: "top right" }

   ];
   const chanceStormWords = [
     { words: " The sky fluffs might get angry today.", image: "rain3.jpg", position: "top right" },
     { words: " I might get scared by the sky booms!", image: "rain1.jpg", position: "top right" },
     { words: " Me and Papa like to sit on the swing and watch lightnings.", image: "rain2.jpg", position: "top right" }

   ];
   const stormWords = [
     { words: " Try not to get scared by the sky booms!", image: "rain3.jpg", position: "top right" },
     { words: " The sky fluffs will be angry today!", image: "rain1.jpg", position: "top right" },
     { words: " Me and Papa like to sit on the swing and watch lightnings.", image: "rain2.jpg", position: "top right" }

   ];
   const snowWords = [
     { words: " Good time for couch snuggles.", image: "night.jpg", position: "bottom center" }

   ];
   const chanceSnowWords = [
     { words: " Good time for couch snuggles.", image: "night.jpg", position: "bottom center" }

   ];
   
   // wind
   const windWords = [
     { words: " The sky fluffs will be running fast today.", image: "grass.jpg", position: "top right" }, 
     { words: " Be careful which way you pees today.", image: "grass.jpg", position: "top right" }

   ];
   
   // perfect weather
   const perfectWords = [
     { words: " It is a great day for lots of walks!", image: "sun1.jpg", position: "center center" }

   ];
   
   
   // assigns dollyWordsObject (stores image and position to use) and adds words to dollyWords
   function randomWords (wordsArray) {
     // pick a random phrase from the array of choices
     dollyWordsObject = wordsArray [ Math.floor ( Math.random() * wordsArray.length ) ];
     // concatenate the small phrase onto the larger whole phrase
     dollyWords += dollyWordsObject.words;
   }

   
   // check the season?
   // check for holiday?


   // level of sunshine
   // If clear
   if (weatherResult.properties.periods[position].shortForecast.startsWith("Clear")) {
       randomWords(clearWords);
   }
   // If mostly clear
   if (weatherResult.properties.periods[position].shortForecast.startsWith("Mostly Clear")) {
       randomWords(clearWords);
   }
   // If partly clear
   if (weatherResult.properties.periods[position].shortForecast.startsWith("Partly Clear")) {
       randomWords(clearWords);
   }
   // if sunny
   else if (weatherResult.properties.periods[position].shortForecast.startsWith("Sunny")) {
     randomWords(sunWords);  
   }
   // if mostly sunny
   else if (weatherResult.properties.periods[position].shortForecast.startsWith("Mostly Sunny")) {
     randomWords(mostSunWords);  
   }
   // if partly sunny
   else if (weatherResult.properties.periods[position].shortForecast.startsWith("Partly Sunny")) {
     randomWords(partCloudWords);  
   }
   // if partly cloudy
   else if (weatherResult.properties.periods[position].shortForecast.startsWith("Partly Cloudy")) {
     randomWords(partCloudWords);  
   }
   // if mostly cloudy
   else if (weatherResult.properties.periods[position].shortForecast.startsWith("Mostly Cloudy")) {
     randomWords(partCloudWords);  
   }
   // if cloudy
   else if (weatherResult.properties.periods[position].shortForecast.startsWith("Cloudy")) {
     randomWords(cloudWords);  
   }


   // temperature
   if (weatherResult.properties.periods[position].temperature <= 32) {
     randomWords(coldWords);  
   } else if (weatherResult.properties.periods[position].temperature <= 50) {
     randomWords(coolWords);  
   } else if (weatherResult.properties.periods[position].temperature >= 90) {
     randomWords(hotWords);  
   } else if (weatherResult.properties.periods[position].temperature >= 80) {
     randomWords(warmWords);  
   }


   // precipitation
   // chance
   if (weatherResult.properties.periods[position].detailedForecast.includes("chance")) {

     if (weatherResult.properties.periods[position].detailedForecast.includes("showers")) {
       randomWords(chanceRainWords);
     }
     if (weatherResult.properties.periods[position].detailedForecast.includes("thunderstorms")) {
       randomWords(chanceStormWords);
     }
     if (weatherResult.properties.periods[position].detailedForecast.includes("snow")) {
       randomWords(chanceSnowWords);
     }
   // full on 100% chance
   } else {
     if (weatherResult.properties.periods[position].detailedForecast.includes("showers")) {
       randomWords(rainWords);
     }
     if (weatherResult.properties.periods[position].detailedForecast.includes("thunderstorms")) {
       randomWords(stormWords);
     }
     if (weatherResult.properties.periods[position].detailedForecast.includes("snow")) {
       randomWords(snowWords);
     }
   }
   
   
   // if windy
   if (weatherResult.properties.periods[position].windSpeed >= 10) {
     randomWords(windWords);  
   }

   // add photo and position to weatherImageArray
   weatherImageArray.push ({ name: dollyWordsObject.image, position: dollyWordsObject.position, alt: dollyWordsObject.words });

   return dollyWords;
 }




 // get latitude and longitude from browser
 function getLocation() {
   if (navigator.geolocation) {
     navigator.geolocation.getCurrentPosition(getWeatherPosition); //takes showPosition as callback function and returns position
   } else {
     alert("Geolocation is not supported by this browser, so here's the weather at Dolly's house in Richmond, Va.");
     badLocation();
   }
 }



 // get latitude and longitude from browser
function badLocation() {
  console.log("Running badLocation");
  let dollyPosition = {coords:{latitude:37.5298923055164, longitude:-77.41065321806}};
  getWeatherPosition(dollyPosition);
}



 
 // look up weather zone and grid position within the zone. also gets city and state.
 function getWeatherPosition(position) {
   let xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
     if (this.readyState == 4 && this.status == 200) {
       positionResult = JSON.parse(this.responseText);
       console.log("Position result json: ");
       console.log(positionResult);

       document.getElementById("location").innerHTML = 
         "<p>Location: <b>" + positionResult.properties.relativeLocation.properties.city + ", " + 
         positionResult.properties.relativeLocation.properties.state +
         "</b> (Latitude: " + position.coords.latitude + ", Longitude: " + position.coords.longitude +
         ")</p>"           
       ;
       //three weather api calls once the longitude and latitude position is returned
       loadWeather(positionResult.properties.gridId, positionResult.properties.gridX, positionResult.properties.gridY);
       getWeatherHourly(positionResult.properties.gridId, positionResult.properties.gridX, positionResult.properties.gridY);
       getWeatherAlert(position.coords.latitude, position.coords.longitude);
     } else if (this.readyState == 4 && this.status == 404) {
        alert("We could not get weather data for that location, so we will give you the forecast for Dolly's house in Richmond, Va.");
        badLocation();
     }

   };
   xhttp.open("GET", "https://api.weather.gov/points/" + position.coords.latitude + "," + position.coords.longitude, true);
   xhttp.send();
 }




 // get and display daily weather report
 // it fetches data (positions 0-13) from weather service API
 // it then adds them to two arrays. one for expanded forecasts. one for abbreviated forecasts
 function loadWeather(office, x, y) {
   let xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
     if (this.readyState == 4 && this.status == 200) {
       weatherResult = JSON.parse(this.responseText);         

       console.log("Daily forecast json: ");
       console.log(weatherResult);

       // store today's forecast into the array
       // if already passed noon, need to make first day just tonight (half day)
       let dayCount = 0; // used to build links to hourly forecasts
       let dayStart = 0; // used to build links to hourly forecasts


       // today's expanded and abbreviated forecasts into the dailyforecast div
       let dailyForecastText = document.getElementById("dailyforecast");
       
       dailyForecastText.innerHTML="";

       // if starting with a half day
       if (weatherResult.properties.periods[0].name == "Tonight" || weatherResult.properties.periods[0].name == "Overnight") {
         
         weatherResult.properties.periods[0].shortForecast = weatherResult.properties.periods[0].shortForecast.replace("Thunderstorm", "Storm");

         dailyForecastText.insertAdjacentHTML("beforeend", `
           <div id="day0" class="daily-full col-xl-3 col-md-5">
             <div id="full0" class="visible">
               <img id="image0" class="backdropimage2">
               <h2> ${weatherResult.properties.periods[0].name}</h2> 
               <p><b>Forecast:</b> ${weatherResult.properties.periods[0].shortForecast}, 
               <b>Temperature:</b> ${weatherResult.properties.periods[0].temperature}, 
               <b>Wind:</b> ${weatherResult.properties.periods[0].windSpeed} ${weatherResult.properties.periods[0].windDirection}
               <br> ${weatherResult.properties.periods[0].detailedForecast}</p>

               <div class="dollysays">
                 <h2>Dolly says</h2> 
                 <p>${dollySays(0, 0, 1)}</p>
               </div>

               <p><a href="#hourly${dayCount}">Hour-by-hour walk forecast</a></p>
             </div>
         
             <div id="abbreviated0" class="hidden" onclick="changeForecast(0, this);">
               <div class="circle">
                 Now
               </div> 
               <p><b> ${weatherResult.properties.periods[0].name}</b> 
               <br>${weatherResult.properties.periods[0].shortForecast}
               <br>${weatherResult.properties.periods[0].temperature}F</p> 
             </div>
           </div>
         `);
         
         dayCount = 1;
         dayStart = 1;
         
       }

       let currentDayAbbreviation;
       let currentDayArray; // used to split holiday names so we can get the first letters for an abbreviation. example Memorial Day abbreviation is MD
       
       //add rest of the full days into the array
       for (i=dayStart; i < weatherResult.properties.periods.length; i=i+2) {          
         
         
         // create abbreviation of the day of the week
         currentDayAbbreviation = "";
         if (weatherResult.properties.periods[i].name == "Today" || weatherResult.properties.periods[i].name == "This Afternoon") {
           currentDayAbbreviation ="Now";
         }
         //if current day has a space (is a special holiday), get first letter then each letter after the space
         else if (weatherResult.properties.periods[i].name.includes(" ")){
           currentDayArray = weatherResult.properties.periods[i].name.split(" ");
           function getFirstLetters(item) {
             currentDayAbbreviation = currentDayAbbreviation + item.slice(0, 1);
           }
           currentDayArray.forEach(getFirstLetters);
         }
         // else just use the first two letters of the day of the week
         else{
           currentDayAbbreviation = weatherResult.properties.periods[i].name.slice(0, 2);
         }
         
         weatherResult.properties.periods[i].shortForecast = weatherResult.properties.periods[i].shortForecast.replace("Thunderstorm", "Storm");

         
         // if full day (has a morning and evening)
         if (i+1 < weatherResult.properties.periods.length) {

           dailyForecastText.insertAdjacentHTML("beforeend", `
             <div id="day${dayCount}" class="${dayCount==0 ?'col-xl-3 col-md-5 daily-full':'col-md-2 col-xxl-1 daily-abbreviated'}">

               <div id="full${dayCount}" class="${dayCount==0 ?'visible':'hidden'}">
                 <img id="image${dayCount}" class="backdropimage2">
                 <h2> ${weatherResult.properties.periods[i].name}</h2> 
                 <p><b>Forecast:</b> ${weatherResult.properties.periods[i].shortForecast}, 
                 <b>Temperature:</b> ${weatherResult.properties.periods[i].temperature}, 
                 <b>Wind:</b> ${weatherResult.properties.periods[i].windSpeed} ${weatherResult.properties.periods[i].windDirection}
                 <br> ${weatherResult.properties.periods[i].detailedForecast}</p>

                 <h2> ${weatherResult.properties.periods[i+1].name}</h2> 
                 <p><b>Forecast:</b> ${weatherResult.properties.periods[i+1].shortForecast}, 
                 <b>Temperature:</b> ${weatherResult.properties.periods[i+1].temperature}, 
                 <b>Wind:</b> ${weatherResult.properties.periods[i+1].windSpeed} ${weatherResult.properties.periods[i+1].windDirection}
                 <br> ${weatherResult.properties.periods[i+1].detailedForecast}</p>

                 <div class="dollysays">
                   <h2>Dolly says</h2> 
                   <p>${dollySays(dayCount, i, 2)}</p>
                 </div>

                 <p><a href="#hourly${ weatherResult.properties.periods[0].name == "Overnight" ? dayCount-1 : dayCount }">Hour-by-hour walk forecast</a></p>
               </div>
               
               <div id="abbreviated${dayCount}" class="${dayCount==0 ?'hidden':'visible'}" onclick="changeForecast(${dayCount-1}, this);">
                 <div class="circle">
                   ${currentDayAbbreviation}
                 </div> 
                 <p><b>${weatherResult.properties.periods[i].name}</b> 
                 <br>${weatherResult.properties.periods[i].shortForecast}
                 <br>${weatherResult.properties.periods[i].temperature}F, 
                 ${weatherResult.properties.periods[i+1].temperature}F</p> 
               </div>

             </div>
           `);
           

         // else add half day to weather results array
         } else {
           dailyForecastText.insertAdjacentHTML("beforeend", `
             <div id="day${dayCount}" class="col-md-2 col-xxl-1 daily-abbreviated">
               <div id="full${dayCount}" class="hidden">
                 <img id="image${dayCount}" class="backdropimage2">
                 <h2> ${weatherResult.properties.periods[i].name}</h2> 
                 <p><b>Forecast:</b> ${weatherResult.properties.periods[i].shortForecast}, 
                 <b>Temperature:</b> ${weatherResult.properties.periods[i].temperature}, 
                 <b>Wind:</b> ${weatherResult.properties.periods[i].windSpeed} ${weatherResult.properties.periods[i].windDirection}
                 <br> ${weatherResult.properties.periods[i].detailedForecast}</p>

                 <div class="dollysays">
                   <h2>Dolly says</h2> 
                   <p>${dollySays(dayCount, i, 1)}</p>
                 </div>

                 <p><a href="#hourly${ weatherResult.properties.periods[0].name == "Overnight" ? dayCount-1 : dayCount }">Hour-by-hour walk forecast</a></p>
               </div>
           
               <div id="abbreviated${dayCount}" class="visible" onclick="changeForecast(${dayCount-1}, this);">
                 <div class="circle">
                   ${currentDayAbbreviation}
                 </div> 
                 <p><b>${weatherResult.properties.periods[i].name}</b> 
                 <br>${weatherResult.properties.periods[i].shortForecast}
                 <br>${weatherResult.properties.periods[i].temperature}F</p> 
               </div>
             </div>
           `);
         }
         dayCount++;
       }
     changeImage(0);

     } else if (this.status == 500){
       let dailyForecastText = document.getElementById("dailyforecast");
       dailyForecastText.innerHTML="<span style='color:yellow'>Something went wrong with the National Weather Service. This page will try again in 5 seconds or try hitting the reload button.</span>";
       
      setTimeout(function(){
        getLocation();
      },5000);
     }
   
   };
   xhttp.open("GET", "https://api.weather.gov/gridpoints/" + office +"/" + x + "," + y + "/forecast", true);
   xhttp.send();
 }




 // swap expanded and abbreviated forecasts. used to pop out forecast with onclick event
 function changeForecast(dayNumber, thisElement) {
   
   // abbreviate old forecast
   let elementsToHide = document.getElementsByClassName("visible");
   for (i=0; i<elementsToHide.length; i++)
   {
     if (elementsToHide[i].id.startsWith("full")){
       elementsToHide[i].classList.add("hidden");
       elementsToHide[i].classList.remove("visible");
       document.getElementById("abbreviated"+i).classList.add("visible");
       document.getElementById("abbreviated"+i).classList.remove("hidden");
     }
   }
   let dayToChange = document.getElementsByClassName("daily-full")[0];
   dayToChange.classList.remove("daily-full", "col-xl-3", "col-md-5");
   dayToChange.classList.add("daily-abbreviated", "col-md-2", "col-xxl-1");

   
   let todayNumber = thisElement.id.charAt(11); //gets number from id abbreviated0 ... abbreviated8

   // setTimeout used to create a delay in animation from time of collapse to time of expand
   setTimeout(function(){

     // expand full new forecast
     thisElement.classList.add("hidden");
     thisElement.classList.remove("visible");
     document.getElementById("full"+todayNumber).classList.add("visible");
     document.getElementById("full"+todayNumber).classList.remove("hidden");

     document.getElementById("day"+todayNumber).classList.add("daily-full", "col-xl-3", "col-md-5");
     document.getElementById("day"+todayNumber).classList.remove("daily-abbreviated", "col-md-2", "col-xxl-1");

   },500);


   // scroll to new forecast (used to align top of screen to new position of expanded forecast)
   if (window.innerWidth < 768){

     var scrollToElement = document.getElementById("day"+todayNumber);
     var scrollToElementOffset = 60;
     var scrollToElementPosition = scrollToElement.getBoundingClientRect().top;
     var scrollToElementOffsetPosition = scrollToElementPosition + window.pageYOffset - scrollToElementOffset;
   
     window.scrollTo({
         top: scrollToElementOffsetPosition,
         behavior: "smooth"
     });
   }

   // change picture
   changeImage(todayNumber);
 }




 // change background image based on day's weather
 // it uses image names and positions stored in weatherImageArray[]
 function changeImage(dayNumber) {
   //console.log("changing " + dayNumber + " image to " + weatherImageArray[dayNumber].name + " " +  weatherImageArray[dayNumber].position);
   let backdropImage = document.getElementsByClassName("backdropimage")[0];
   backdropImage.style.backgroundImage = `url('images/${weatherImageArray[dayNumber].name}')`;
   backdropImage.style.backgroundPosition = weatherImageArray[dayNumber].position;

   //set small image that appears in daily forecast in small screen size
   let smallImage = document.getElementById("image"+dayNumber);
   smallImage.src = `images/${weatherImageArray[dayNumber].name}`;
   smallImage.alt = weatherImageArray[dayNumber].alt;
 }


 let walkStartTime = 6;
 let walkEndTime = 20;
 let walkTempMin = 40;
 let walkTempMax = 90;
 let walkPrecipitation = 0;


 // get and display hourly weather report
 function getWeatherHourly(office, x, y) {
   let xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
     if (this.readyState == 4 && this.status == 200) {
       weatherResultHourly = JSON.parse(this.responseText);
       
       console.log("Hourly forecast json: ");
       console.log(weatherResultHourly);

       // print the hourly forecast into the div with the hourlyforecast id
       let hourlyForecastText = document.getElementById("hourlyforecast");
       hourlyForecastText.innerHTML = "<h2>Hour-by-hour walk forecast</h2><p>(<b>Ideal walking weather:</b> 6 a.m. to 8 p.m. 40 to 89 degrees and no precipitation.)</p>";
       
       // used to format date. used to convert number into string
       const months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
       const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];

       let dayCount = 0; // keeps track of the number of days printed

       for (i=0; i <weatherResultHourly.properties.periods.length; i++) {
         
         // convert string from json into a proper date
         let startTime = new Date(weatherResultHourly.properties.periods[i].startTime);
         
         // if first loop, create initial div and header
         if (i==0) {
           hourlyForecastText.insertAdjacentHTML("beforeend", `
           <a id="hourly${dayCount}"></a>
           <div class='hourly'>  
             <h3>${days[startTime.getDay()]}, ${months[startTime.getMonth()]} ${startTime.getDate()}, ${startTime.getFullYear()}</h3>
           </div>
           `);
         }

         // create new div and header if the start of a new day
         if (startTime.getHours()==0 && i!==0) {
           dayCount++;
           hourlyForecastText.insertAdjacentHTML("beforeend", `
           <a id="hourly${dayCount}"></a>
           <div class='hourly'>  
               <h3>${days[startTime.getDay()]}, ${months[startTime.getMonth()]} ${startTime.getDate()}, ${startTime.getFullYear()}</h3>
             </div>
           `);
         }

         // insert text into most recent date's div
         // print formatted time
         if (startTime.getHours()==0) {
           hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
             <b>Midnight, </b>
           `);
         } else if (startTime.getHours() < 12)  {
           hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
             <b>${startTime.getHours()} a.m., </b> 
           `);
         } else if (startTime.getHours() == 12) {
           hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
             <b>Noon, </b>
           `);
         } else {
           hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
             <b>${startTime.getHours()-12} p.m., </b>
           `);
         }

         // print forecast, temperature and wind
         hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
           ${weatherResultHourly.properties.periods[i].shortForecast}, 
           ${weatherResultHourly.properties.periods[i].temperature}F, 
           wind ${weatherResultHourly.properties.periods[i].windSpeed} ${weatherResultHourly.properties.periods[i].windDirection} 
         `);

         // is good for walk?
         if (weatherResultHourly.properties.periods[i].temperature >= walkTempMin && weatherResultHourly.properties.periods[i].temperature < walkTempMax &&
             startTime.getHours() >= walkStartTime && startTime.getHours() <= walkEndTime && 
             (weatherResultHourly.properties.periods[i].shortForecast == "Sunny" || 
             weatherResultHourly.properties.periods[i].shortForecast == "Mostly Sunny" ||
             weatherResultHourly.properties.periods[i].shortForecast == "Partly Sunny" ||
             weatherResultHourly.properties.periods[i].shortForecast == "Partly Cloudy" ||
             weatherResultHourly.properties.periods[i].shortForecast == "Mostly Cloudy" ||
             weatherResultHourly.properties.periods[i].shortForecast == "Cloudy" || 
             weatherResultHourly.properties.periods[i].shortForecast == "Clear" || 
             weatherResultHourly.properties.periods[i].shortForecast == "Mostly Clear" || 
             weatherResultHourly.properties.periods[i].shortForecast == "Partly Clear")) {
           hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
           <b><span style="color:red">(WALK)</span></b> 
         `);
         }

         hourlyForecastText.lastElementChild.insertAdjacentHTML("beforeend", `
           <br>
         `);

       }
     } else if (this.status == 500){
      
       let dailyForecastText = document.getElementById("hourlyforecast");
       dailyForecastText.innerHTML="Something went wrong with the National Weather Service. Try hitting the reload button.";

     }
   };
   xhttp.open("GET", "https://api.weather.gov/gridpoints/" + office +"/" + x + "," + y + "/forecast/hourly", true);
   xhttp.send();
 }





 // get and display weather alerts
 // example api call: https://api.weather.gov/alerts/active?point=37.52985065563401,-77.41054289211888
 function getWeatherAlert(latitude, longitude) {
   let xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
     if (this.readyState == 4 && this.status == 200) {
       
       weatherAlert = JSON.parse(this.responseText);
       
       console.log("Weather alert json: ");
       console.log(weatherAlert);

       // print the hourly forecast into the div with the hourlyforecast id
       let alertText = document.getElementById("weatheralertbody");

       // checks to see if alerts exist
       if (weatherAlert.features.length==0){
         alertText.innerHTML = `
           <p>There are no active weather alerts for your location. </p>
         `;
       
       // loop through alerts and display if they exist
       } else {

         document.getElementById("weatheralertouter").style.display = "block";

         alertText.innerHTML = "";
         for (i=0; i<weatherAlert.features.length; i++) {
           alertText.insertAdjacentHTML("beforeend", `
               <h3>${weatherAlert.features[i].properties.event}</h3> 
               <p><b>${weatherAlert.features[i].properties.headline}</b> 
               ${weatherAlert.features[i].properties.description}</p>
           `);
           if (weatherAlert.features[i].properties.instruction !== null) {
           alertText.insertAdjacentHTML("beforeend", `
               <p>${weatherAlert.features[i].properties.instruction}</p>
           `);}
         }

       }
     }
   };
   xhttp.open("GET", `https://api.weather.gov/alerts/active?point=${latitude},${longitude}`, true);
   xhttp.send();
 }