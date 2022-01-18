import Link from 'next/link';

const Horizontalnavbar = () => (



<div style={{textAlign: "left", width:"100%"}}>
<img src='../static/images/hillarytitle.jpg'  style={{width:"100%"}}></img>





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

h1 {
  padding:20px;
}




`}</style> 


</div>



	);

export default Horizontalnavbar;