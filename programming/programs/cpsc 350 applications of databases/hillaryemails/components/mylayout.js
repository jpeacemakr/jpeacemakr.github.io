


const MyLayout = (props) => (

 //<div>
 <body>
 {props.children}
  

<style jsx>{`

a:link, a:visited {
  color: #669999;
  text-decoration: none;
  display: inline-block;
}



a:hover {
  color: #336666;
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


`}</style> 

</body>
//  </div>






);

export default MyLayout;
