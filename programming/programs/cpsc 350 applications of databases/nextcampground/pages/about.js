import Horizontalnavbar from '../components/Horizontalnavbar';
import MyLayout from '../components/MyLayout';
import Footer from '../components/Footer';
import Link from 'next/link'

const Index = () => (

	<html>
	<head>
	<title>Campground.org: About Us</title>

	</head>


	<MyLayout>
		<Horizontalnavbar />
		
		<div className="aboutbox">
			<img className="james" src="../static/images/james.jpg"/>
			<h2>About this website</h2>
			<p>This is obviously not a real website. It is a class project by James Peacemaker, a computer science major at the University of Mary Washington in Fredericskburg, Va. The class is CPSC 350, Applications of Databases, taught by Ron Zacharski.
				This project uses Next.js to create a front end for a campground search api.</p>
		</div>
		
		<Footer />


		<style jsx>{`
			
			.aboutbox {
				background-color:#EEEEEE; 
				padding:40px;
				margin:40px;

			}

			.james {
				margin:20px;
				float:right; 
				width: 300px;
				height: 300px;



			}

		`}</style> 

	</MyLayout>

	</html>


);

export default Index;
