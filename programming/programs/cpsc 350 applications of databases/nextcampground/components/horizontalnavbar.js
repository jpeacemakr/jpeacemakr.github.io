import Link from 'next/link';

const Horizontalnavbar = () => (


<div>

<Link href="index">
      <a>HOME</a>
    </Link>|
<Link href="search">
      <a>SEARCH</a>
    </Link>|
<Link href="about">
      <a>ABOUT</a>
    </Link>


<style jsx>{`
a:link, a:visited {
  background-color: #000000;
  color: white;
  padding: 15px 22px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
}

a:hover {
  background-color: #336699;
  color: white;
  padding: 15px 22px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
}


p {
  color: yellow;
  font-family:Helvetica;
  margin:0;
}

div {
  background-color: #000000;
  color: yellow;
  font-family:Helvetica;
  margin:0;
}

`}</style> 


</div>



	);

export default Horizontalnavbar;