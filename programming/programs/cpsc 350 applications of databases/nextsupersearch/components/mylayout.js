


const MyLayout = (props) => (

 //<div>
 <body>
 {props.children}
  

<style jsx>{`

a:link, a:visited {
  color: white;
  text-decoration: none;
  display: inline-block;
}

a:hover {
  color: pink;
  text-decoration: none;
  display: inline-block;
}


div {
  color: black;
  font-family:Helvetica;
  margin:0;
}

body {
  color: black;
  font-family:Helvetica;
  margin:0;
  padding:0;
}

p {
  color: black;
  font-family:Helvetica;
  margin:0;
  padding:0;
}

h2 {
  color: #336699;
}

`}</style> 

</body>
//  </div>






);

export default MyLayout;
