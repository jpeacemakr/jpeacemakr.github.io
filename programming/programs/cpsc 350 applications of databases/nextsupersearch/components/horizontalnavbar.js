import Link from 'next/link';
import jsCookie from "js-cookie";





const Horizontalnavbar = () => (



<div style={{textAlign: "center", width:"100%"}}>
<img src='../static/images/supersearch.jpg'  style={{width:"80%"}}></img>
<div style={{textAlign: "right", width:"100%"}}>



      

      { jsCookie.get("name") ? 
<>
      <>[ Signed in as {jsCookie.get("name")}. Showing results for the {jsCookie.get("zip")} zip code. ]&nbsp;&nbsp;&nbsp;&nbsp;</>
      <Link href="/logout">
        <a>Logout</a>
      </Link> 
      <Link href="/">
        <a>Home</a>
      </Link>
 
</>
       :
<>
      <>[ Log in to show results for your zip code. ]&nbsp;&nbsp;&nbsp;&nbsp;</> 
      <Link href="/login">
        <a>Login</a>
      </Link>     
      <Link href="/createuser">
        <a>Register</a>
      </Link>     
      <Link href="/">
        <a>Home</a>
      </Link>
 </>

      }
 
</div>  



<style jsx>{`
a:link, a:visited {
  background-color: #336699;
  color: white;
  padding: 15px 22px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
}

a:hover {
  background-color: #6699CC;
  color: white;
  padding: 15px 22px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
}


p {
  color: yellow;
  background-color: #336699;
  font-family:Helvetica;
  margin:0;
}

div {
  background-color: #FFFFFF;
  color: #336699;
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