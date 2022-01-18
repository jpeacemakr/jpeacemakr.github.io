import Link from 'next/link';

const Footer = () => (


<div>

<Link href="index"><a>Campgrounds.org</a></Link> is part of the Peacemaker Media Empire. Copyright 2019. | <Link href="mailto:jpeacemakr@gmail.com">
     <a>Contact us.</a>
    </Link>


<style jsx>{`
a:link, a:visited {
  color: #6699CC;
  text-decoration: none;
  display: inline-block;
}



a:hover {
  color: #336699;
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