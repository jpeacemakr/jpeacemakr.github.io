import Link from 'next/link';

const Footer = () => (


<div>

<Link href="index"><a>NutritionFinder.com</a></Link> is part of the Peacemaker Media Empire. Copyright 2019. 


<style jsx>{`
a:link, a:visited {
  color: #336633;
  text-decoration: none;
  display: inline-block;
}



a:hover {
  color: #669966;
}


p {
  color: black;
  font-family:Helvetica;
  margin:0;
}

div {
  color: black;
  font-family:Helvetica;
  margin:40px;
  text-align:left;
  font-size:80%;
}

`}</style> 


</div>



	);

export default Footer;
