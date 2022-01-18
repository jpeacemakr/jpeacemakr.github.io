import React, { useState } from 'react';

import { IonContent, 
  IonAlert, 
  IonHeader, 
  IonTextarea, 
  IonPage, 
  IonTitle, 
  IonToolbar, 
  IonFooter, 
  IonButton } from '@ionic/react';
import './Tab3.css';

import { useFirebase } from '../hooks/useFirebase';
import { useShout } from '../hooks/useShout';



const Tab3: React.FC = () => {

  const { shouttext, setShouttext, createShoutGPSWithToken } = useShout();
  const { getEmail, logUser } = useFirebase();

  const [showAlert1, setShowAlert1] = useState(false);


  return (
    <IonPage>

      <IonHeader>

        <IonToolbar color="primary">
          <IonTitle>Shout your location: {getEmail()}</IonTitle>
        </IonToolbar>

      </IonHeader>
      

      <IonContent>
        
        <IonAlert
          isOpen={showAlert1}
          onDidDismiss={() => setShowAlert1(false)}
          header={'Your shout has been sent.'}
          buttons={['OK']}
        />

        { 

          logUser() ?

          <div style={{ padding:"15px", margin:"15px" }}>

            {/*<IonInput value={getShouttext()} placeholder='Type your shout here.' type='text' onIonChange={e => setShouttext(e.detail.value!)} ></IonInput>*/}

            <IonTextarea rows={8} value={shouttext} placeholder='Type your shout here.' onIonChange={e => setShouttext(e.detail.value!)} ></IonTextarea>

          </div>

         : 

        <div style={{ padding:"15px", margin:"15px" }}>

          <p> You must be logged in to post shouts.</p>

        </div>

        }


      </IonContent>



      <IonFooter style={{textAlign:"center", background:"#99CCFF", padding:"15px"}}>
          
          {/*<IonButton onClick={() => createShout({username:getEmail(), shouttext:shouttext, longitude: -1.2323, latitude: 1.98774 })}>SHOUT YOUR FAKE LOCATION</IonButton>*/}
       
          {/*<IonButton onClick={() => createShoutGPS(shouttext)}>SHOUT YOUR LOCATION</IonButton>*/}

          <IonButton onClick={() => {createShoutGPSWithToken(shouttext); setShowAlert1(true)}}>SHOUT YOUR LOCATION</IonButton>
        

      </IonFooter>


    </IonPage>
  );
};

export default Tab3;
