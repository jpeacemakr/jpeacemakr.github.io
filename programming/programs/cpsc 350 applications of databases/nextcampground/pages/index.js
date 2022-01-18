import Horizontalnavbar from '../components/Horizontalnavbar';
import MyLayout from '../components/MyLayout';
import Footer from '../components/Footer';
import Link from 'next/link'



const Index = () => (

<html>
<head>
	<title>Campground Finder</title>

</head>


	
    <MyLayout>
<Horizontalnavbar />
    <img src="static/images/home.jpg" width="100%" />
  	

<div className="row">
  		
  		<div className="column">
  		<img src="static/images/hikesmall2.jpg" width="100%" />
  		<h2><Link href="#"><a>Top picks</a></Link></h2>
  		Campgrounds.org highlights the best camping locations aross the United States. Here is some text that explains what the website is about.</div>

  		<div className="column">
  		<img src="static/images/hikesmall3.jpg" width="100%" />
  		<h2><Link href="#"><a>Hiking with history</a></Link></h2>
  		Campgrounds.org highlights the best camping locations aross the United States. Here is some text that explains what the website is about.</div>
		
		<div className="column">
		<img src="static/images/hikesmall1.jpg" width="100%" />
		<h2><Link href="#"><a>Bring the kids</a></Link></h2>
		Campgrounds.org highlights the best camping locations aross the United States. Here is some text that explains what the website is about.</div>
	
</div>
  		
 
 

  	
	<Footer />


  	<style jsx>{`

		body{
			border:0;
			padding:0;
			margin:0;
		}
			
		div.row {
		  float: left;
		  width: 90%;
		  padding: 10px;
		}

		div.column {
		  float: left;
		  width: 25%;
		  padding: 30px;
		}

		h2{
			color:#6699CC;
			line-height: 0.5em;
		}
	
		a:link, a:visited {
	  		color: #6699CC;
	  		text-decoration: none;
			display: inline-block;
		}

		a:hover {
 		 color: #336699;
		}
		


	`}</style> 

  	</MyLayout>

</html>




 );

 export default Index;
