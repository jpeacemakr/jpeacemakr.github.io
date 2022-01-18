import React from 'react';

import './Tab2.css';

import { IonButton, 
  IonContent, 
  IonHeader, 
  IonFooter, 
  IonPage, 
  IonTitle, 
  IonToolbar } from '@ionic/react';

import { useShout } from '../hooks/useShout';
import { useFirebase } from '../hooks/useFirebase';


const Tab2: React.FC = () => {

  const { getEmail } = useFirebase();
  const { shoutRead, 
    //getShouttextlist, 
    getShoutlist } = useShout();


  //logs user email to console. for testing only.
  /*function logUserOnPush () {
    console.log(getEmail());
    return 1;
  }*/


  //logs shout list to console. for testing only.
  /*function displayShouts ()
    {
      
      let currentShoutList = getShoutlist();
      let currentShoutTextList = getShouttextlist();

      console.log("currentShoutList in displayShouts", currentShoutList);
      console.log("currentShoutTextList in displayShouts", currentShoutTextList);
    }*/



  return (
    <IonPage>

      <IonHeader>

        <IonToolbar  color="primary">
          <IonTitle>Shouts near you: {getEmail()}</IonTitle>
        </IonToolbar>

      </IonHeader>



      <IonContent>

        <div style={{ padding:"15px", margin:"15px" }}>

         {/*<IonButton onClick={() => logUser()}>Log the user to the console</IonButton>*/}
         {/*<IonButton onClick={() => logUserOnPush()}>Log the user to the console</IonButton>*/}

           <p>
           {/* getShouttextlist() */}
           </p>
           
           { 

            getShoutlist() ?

              <>{/* displayShouts() */}
  
              <p>Click the "Load Shouts" button below to refresh the list.</p>

              <ul>{ getShoutlist().map((item:any) => 
                (<li key={item._id}> 
                <b>{item.username}:</b>  
                <i>(longitude: {item.longitude},  
                latitude: {item.latitude}, 
                time: {item.time}, {item.date}):</i><br /> 
                {item.shouttext} 
                </li>)) }</ul>

              </>

          : 

            <p>Click "Load Shouts" button below to see what's happening near you.</p>
          
          }
           
        </div>

      </IonContent>


      <IonFooter style={{textAlign:"center", background:"#99CCFF", padding:"15px"}}>

         <IonButton onClick={() => shoutRead(0,0,0)}>Load shouts</IonButton>

      </IonFooter>




    </IonPage>
  );
};

export default Tab2;
