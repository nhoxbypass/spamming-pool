import React, { Component } from "react";
import {
    View,
    Text,
    TextInput,
    Button,
    Image,
    StyleSheet,
    AsyncStorage
} from "react-native";
import SegmentedControlTab from "react-native-segmented-control-tab";
import styles from './styles.js';

export default class Calculator extends Component {
    constructor(props) {
        super(props);
        this.state = {
            selectedIndex: 0,
            billAmount: 0,
            tipPercent: 10,
            tipAmount: 0,
            result: 0,
            firstPercentValue: 10,
            secondPercentValue: 20,
            thirdPercentValue: 30
        };
    }

    static navigationOptions = {
        drawerLabel: 'Calculator',
        drawerIcon: ({tintColor}) => (
            <Image
                source={require('./../../res/images/icon_calculator.png')}
                style={[styles.icon, {tintColor: tintColor}]}
            />
        )
    };

    componentWillMount() {
        this.loadPercentageValue();
    }

    render() {
        return (
            <View style={styles.container}>
                <View>
                    <Text style={styles.title}>Tip Calculator</Text>
                </View>
                <View style={{ flexDirection: 'row', alignItems: 'center' }}>
                    <Text style={styles.label}>Bill amount:</Text>
                    <TextInput
                        style={styles.billInput}
                        placeholder='Input bill amount...'
                        keyboardType='numeric'
                        onChangeText={this.handleBillAmountChange}></TextInput>
                </View>
                <View>
                    <Text style={styles.label}>Tip amount: ${this.state.tipAmount}</Text>
                </View>
                <View style={styles.segmentedControlTab}>
                    <SegmentedControlTab
                        values={[this.state.firstPercentValue + '%', this.state.secondPercentValue + '%', this.state.thirdPercentValue + '%']}
                        selectedIndex={this.state.selectedIndex}
                        onTabPress={this.handleIndexChange}
                    />
                </View>
                <View>
                    <Text style={styles.highlightLabel}>Summary</Text>
                    <View style={styles.blackLine}></View>
                    <View style={{ flexDirection: 'row', alignItems: 'center' }}>
                        <Text style={styles.label}>Bill amount:</Text>
                        <Text style={styles.rightLabel}>${this.state.billAmount}</Text>
                    </View>
                    <View style={{ flexDirection: 'row', alignItems: 'center', marginTop: 8 }}>
                        <Text style={styles.label}>Tip amount:</Text>
                        <Text style={styles.rightLabel}>${this.state.tipAmount}</Text>
                    </View>
                    <View style={{ flexDirection: 'row', alignItems: 'center', marginTop: 8 }}>
                        <Text style={styles.label}>Percent:</Text>
                        <Text style={styles.rightLabel}>{this.state.tipPercent}%</Text>
                    </View>
                </View>
                <View style={styles.blackLine}></View>
                <View>
                    <View style={{ flexDirection: 'row', alignItems: 'center' }}>
                        <Text style={styles.highlightLabel}>Result: </Text>
                        <Text style={styles.highlightRightLabel}>${this.state.result}</Text>
                    </View>
                </View>
            </View>
        );
    }

    handleIndexChange = (index) => {
        var tipPercent = this.getTipPercent(index);
        var tipAmount = this.calculateTips(this.state.billAmount, tipPercent);
        var result = parseInt(this.state.billAmount, 10) + tipAmount;

        this.setState({
            selectedIndex: index,
            tipPercent: tipPercent,
            tipAmount: tipAmount,
            result: result
        });
    }

    handleBillAmountChange = (billAmount) => {
        var tipPercent = this.getTipPercent(this.state.selectedIndex);
        var tipAmount = this.calculateTips(billAmount, tipPercent);
        var result = parseInt(billAmount, 10) + tipAmount;

        this.setState({
            billAmount: billAmount,
            tipPercent: tipPercent,
            tipAmount: tipAmount,
            result: result
        });
    }

    calculateTips = (billAmount, percent) => {
        return billAmount * percent / 100;
    }

    getTipPercent = (index) => {
        switch (index) {
            case 0:
                return this.state.firstPercentValue;
            case 1:
                return this.state.secondPercentValue;
            case 2:
                return this.state.thirdPercentValue;
            default:
                return this.state.firstPercentValue;
        }
    }

    async loadPercentageValue() {
        try {
            let firstValue = await AsyncStorage.getItem('PERCENT_1_VALUE');
            if (firstValue !== null)
                this.setState({ firstPercentValue: parseFloat(firstValue) });

            let secondValue = await AsyncStorage.getItem('PERCENT_2_VALUE');
            if (secondValue !== null)
                this.setState({ secondPercentValue: parseFloat(secondValue) });

            let thirdValue = await AsyncStorage.getItem('PERCENT_3_VALUE');
            if (thirdValue !== null)
                this.setState({ thirdPercentValue: parseFloat(thirdValue) });
        } catch (error) {
            console.log(error);
        }
    }
}

module.exports = Calculator;