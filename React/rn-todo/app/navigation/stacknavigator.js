import React, { Component } from 'react';
import {
    View
} from 'react-native';
import { StackNavigator } from 'react-navigation';
import Home from '../components/home/home.js';
import TodoAdd from '../components/todoadd/todoadd.js';

export const RootNavigator = StackNavigator({
    Home: {
        screen: Home
    },
    TodoAdd: {
        screen: TodoAdd
    }
}, {
    initialRouteName: 'Home'
});