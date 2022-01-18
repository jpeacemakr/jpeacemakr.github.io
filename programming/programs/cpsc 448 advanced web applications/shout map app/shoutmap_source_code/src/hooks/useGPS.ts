import { Plugins } from '@capacitor/core';
import { useState } from "react";




export function useGPS() {

	//creates GPS in state and sets default to 0.0
	const [GPSlongitude, setGPSlongitude] = useState<Number>(0.0);
	const [GPSlatitude, setGPSlatitude] = useState<Number>(0.0);


	const { Geolocation } = Plugins;



	const newGPS = async () => {
		
		const coordinates = await Geolocation.getCurrentPosition();
		console.log('Current', coordinates);

		var longitude = coordinates.coords.longitude;
		console.log('longitude', longitude);
		
		var latitude = coordinates.coords.latitude;
		console.log('latitude', latitude);
		
		return coordinates;
	}


	const getGPSlongitude = async () => {
		
		const coordinates = await Geolocation.getCurrentPosition();
		console.log('Current', coordinates);

		var longitude = coordinates.coords.longitude;
		console.log('longitude', longitude);
				
		return longitude;
	}


	const getGPSlatitude = async () => {
		
		const coordinates = await Geolocation.getCurrentPosition();
		console.log('Current', coordinates);
		
		var latitude = coordinates.coords.latitude;
		console.log('latitude', latitude);
		
		return latitude;
	}



	return {
	    newGPS, 
	    getGPSlongitude,
	    getGPSlatitude
	};

	



}