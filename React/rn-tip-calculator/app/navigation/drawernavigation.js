import React from 'react';
import {
    View,
    Text
} from 'react-native';
import Calculator from './../components/calculator/calculator.js';
import { DrawerNavigator } from 'react-navigation';
import Settings from './../components/settings/settings.js';

export const RootDrawer = DrawerNavigator({
    Calculator: {
        screen: Calculator
    },
    Settings: {
        screen: Settings
    }
}, {
        initialRouteName: 'Calculator',
        drawerPosition: 'left'
    });