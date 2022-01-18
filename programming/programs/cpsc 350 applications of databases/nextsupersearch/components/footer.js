import Link from 'next/link';

const Footer = () => (


<div>

<Link href="index"><a>Super.Search</a></Link> is part of the Peacemaker Media Empire. Copyright 2019. 


<style jsx>{`
a:link, a:visited {
  color: #336699;
  text-decoration: none;
  display: inline-block;
}



a:hover {
  color: #6699CC;
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
  text-align:center;
  font-size:80%;
}

`}</style> 


</div>



	);

export default Footer;
