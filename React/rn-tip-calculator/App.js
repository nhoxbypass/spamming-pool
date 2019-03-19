import React, { Component } from 'react';
import {
  Text,
  View,
  AsyncStorage
} from 'react-native';
import Calculator from './app/components/calculator/calculator.js';
import { RootDrawer } from './app/navigation/drawernavigation';

export default class App extends Component<{}> {
  render() {
    return (
      <RootDrawer />
    );
  }

  async loadTransitionValue() {
    try {
      let value = await AsyncStorage.getItem('TRANSITION_VALUE');
      if (value !== null)
        this.setState({ screenTransition: value });
    } catch (error) {
      console.log(error);
    }
  }
}