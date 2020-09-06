import React, { useState } from 'react';
import logo from './logo.png';
import {TextField, PrimaryButton, ActionButton} from 'office-ui-fabric-react'
import { GoogleLogin } from 'react-google-login';
import FacebookLogin from 'react-facebook-login';
import './App.css';

function App() {
  const [connected, setConnected] = useState(false);
  const [error, setError] = useState('');
  
  const [firstName, setFirstName] = useState('');
  const [lastName, setLastName] = useState('');
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('');

  const responseFacebook = (response) => {
    if(response.accessToken && !connected){
      setConnected(true);
      setError(false);
    }
    else{
      setError('There was an error logging you in. Please try again.');
    }
  };

  const login = () =>{
    if(!connected){
      setConnected(true);
      setError(false);
    }
  };

  const showError = () =>{
    setConnected(false);
    setError('There was an error logging you in. Please try again.');
  };

  const logout = () =>
  {
    if(connected){
      setConnected(false);
      setError('');
    }
  };

  const setInput = (field, value) => {
    if(field == "FirstName"){
      setFirstName(value);
    }
    else if(field == "LastName"){
      setLastName(value);
    }
    else if(field == "Email"){
      setEmail(value);
    }
    else if(field == "Password"){
      console.log(value);
      setPassword(value);
    }
  };

  const registerUser = () =>{
    if(!firstName || !lastName || !email || !password){
      setError('Please fill all your details in the given fields');
      return;
    }

    var json;
    if(email && password && email!='' && password!=''){
      json = {
        "email": email,
        "password": password
      }
    }
    else if(email && email!=''){
      json = {
        "email": email
      }
    }
    else if(password && password!=''){
      json = {
        "password": password
      }
    }

    const requestOptions = {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(json)
    };

    fetch('https://reqres.in/api/register', requestOptions)
      .then(response => response.json())
      .then(data => {
        if(data.error){
          setError(data.error);
        }
        else{
          setConnected(true);
        }
      });
  };

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} alt="logo image"/>
      </header>
      {
        connected ?
        <div className="container">
          Logged in!
          <br/>
          <ActionButton onClick={logout}>Click here to log out.</ActionButton>
        </div> :
        <>  
          <div className="container"> 
            <div className="signup-box">
              <div className="content">
                <span className="small-text"><b>SIGN UP</b></span>
                <span className="big-text">Create your account</span>
                <span className="small-text"> Lorem ipsum dolor sit amet, consectetur adipiscing elit</span>
                {error && <span className="error-text small-text">{error}</span>}
                <div className="login-buttons">
                  <GoogleLogin
                    clientId="434831295422-g0vj1kat50qlfvaul56sk0veam0oi147.apps.googleusercontent.com"
                    buttonText="Sign up with Google"
                    onSuccess={login}
                    onFailure={showError}
                  />
                  <FacebookLogin
                    appId="684215652184878"
                    fields="name,email"
                    icon="fa-facebook"
                    size="medium"
                    textButton="Sign up with Facebook"
                    callback={responseFacebook}
                  />
                </div>
                <div className="separator">or</div>
                <TextField placeholder="First Name" onChange={(e, value) =>setInput("FirstName", value)}/>
                <TextField placeholder="Last Name" onChange={(e, value) =>setInput("LastName", value)}/>
                <TextField placeholder="Email Address" onChange={(e, value) =>setInput("Email", value)}/>
                <TextField type="password" placeholder="Password" onChange={(e, value) =>setInput("Password", value)}/>
                <span className="small-text">By clicking Sign Up, you agree to our <span className="link">Terms of Use </span>and our <span className="link">Privacy Policy</span>.</span>
                <PrimaryButton onClick={registerUser}>Sign up</PrimaryButton>
              </div>
            </div>
          </div>
      </>
    }
    </div>
  );
}

export default App;
