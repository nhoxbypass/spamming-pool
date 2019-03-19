import React, { Component } from 'react';
import {
    View,
    Text
} from 'react-native';

export default class TodoAdd extends Component {
    render() {
        return (
            <View>
                <Text>TodoAdd screen</Text>
            </View>
        )
    }

    static navigationOptions = {
        title: 'TodoAdd',
    }
}

module.exports = TodoAdd