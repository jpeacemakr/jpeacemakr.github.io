import Layout from "../components/mylayout.js";
import Router from "next/router";
import jsCookie from "js-cookie";


class Logout extends React.Component {


constructor(props) {
    super(props);
    this.state = { username:"", password:"", username:"", zip: "", status:"" };
    jsCookie.remove('name');
    jsCookie.remove('username');
    jsCookie.remove('password');
    jsCookie.remove('zip');
  
  }

//componentDidMount executes as soon as you render the page. In this case it replaes the page with the search page.  
componentDidMount(){
     Router.replace("/");
  }

render() {

	const that = this;
	return (
		<div>You are now logged out.</div>
	)

}

}
export default Logout;
