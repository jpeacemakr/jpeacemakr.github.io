import MyLayout from '../../components/mylayout.js';
import fetch from 'isomorphic-unfetch';
import {getId} from '../../lib/utils.js';

const Post = props => (
  <MyLayout>
  	<div style={{textAlign: 'left', padding:'40px', background:'#FFFFFF'}}>
  	<p>
  	<b>Date sent:</b> {props.searchAgainResult.hits.hits[0]._source.MetadataDateSent.replace("T"," ").replace("+00:00","")}
  	</p>
  	<p>
  	
  	<b>Subject:</b> {props.searchAgainResult.hits.hits[0]._source.MetadataSubject}
  	</p>
  	<p>
  	
  	<b>To:</b> {props.searchAgainResult.hits.hits[0]._source.MetadataTo}
  	</p>
  	<p>
  	
  	<b>From:</b> {props.searchAgainResult.hits.hits[0]._source.MetadataFrom}
  	</p>
  	<p>
  	{props.searchAgainResult.hits.hits[0]._source.RawText}
	</p>
	</div>

  </MyLayout>
);

Post.getInitialProps = async function(context) {
  console.log("context.query");
  console.log(context.query.id);
  const searchAgainResult = await getId(context.query.id);


  return { searchAgainResult} ;
};

export default Post;