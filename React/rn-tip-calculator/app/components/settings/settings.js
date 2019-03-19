import React, { Component } from "react";
import {
    View,
    Text,
    Button,
    TextInput,
    Picker,
    TouchableOpacity,
    Modal,
    Slider,
    Image,
    TouchableWithoutFeedback,
    StyleSheet,
    AsyncStorage
} from "react-native";
import styles from './styles.js';

export default class Settings extends Component {
    constructor(props) {
        super(props);
        this.state = {
            screenTransition: "FloatFromRight",
            modalVisibled: false,
            firstPercentValue: 10,
            secondPercentValue: 20,
            thirdPercentValue: 30
        }
    }

    static navigationOptions = {
        drawerLabel: 'Settings',
        drawerIcon: ({tintColor}) => (
            <Image
                source={require('./../../res/images/icon_settings.png')}
                style={[styles.icon, {tintColor: tintColor}]}
            />
        )
    };

    componentDidMount() {
        this.loadTransitionValue();
        this.loadPercentageValue();
    }

    render() {
        return (
            <View style={styles.container}>
                <View style={styles.itemContainer}>
                    <Text style={styles.label}>Screen transition</Text>
                    <Picker
                        selectedValue={this.state.screenTransition}
                        onValueChange={this.onScreenTransitionValueChange}>
                        <Picker.Item label="FloatFromRight" value="FloatFromRight" />
                        <Picker.Item label="FloatFromLeft" value="FloatFromLeft" />
                        <Picker.Item label="FloatFromBottom" value="FloatFromBottom" />
                        <Picker.Item label="FloatFromBottomAndroid" value="FloatFromBottomAndroid" />
                        <Picker.Item label="SwipeFromLeft" value="SwipeFromLeft" />
                        <Picker.Item label="HorizontalSwipeJump" value="HorizontalSwipeJump" />
                        <Picker.Item label="HorizontalSwipeJumpFromRight" value="HorizontalSwipeJumpFromRight" />
                    </Picker>
                </View>

                <View style={styles.itemContainer}>
                    <TouchableOpacity
                        style={{ flexDirection: 'row', alignItems: 'center', marginTop: 16, marginBottom: 16 }}
                        onPress={() => { this.toggleModal(true) }}>
                        <Text style={styles.label}>Change default tips percent</Text>
                    </TouchableOpacity>
                    <Modal
                        transparent={true}
                        visible={this.state.modalVisibled}
                        onRequestClose={this.onRequestClose}>
                        <TouchableOpacity
                            style={styles.modalOuterContainer}
                            onPress={() => { this.toggleModal(false) }}>
                            <TouchableWithoutFeedback>
                                <View style={styles.modalInnerContainer}>
                                    <View style={{ flexDirection: 'row', alignItems: 'center' }}>
                                        <Text style={styles.flexLabel}>Percentage 1: {this.state.firstPercentValue}%</Text>
                                        <Slider
                                            style={styles.slider}
                                            value={this.state.firstPercentValue}
                                            minimumValue={0}
                                            maximumValue={100}
                                            step={5}
                                            onValueChange={(newValue) => this.setState({ firstPercentValue: newValue })} />
                                    </View>
                                    <View style={{ flexDirection: 'row', alignItems: 'center', marginTop: 8 }}>
                                        <Text style={styles.flexLabel}>Percentage 2: {this.state.secondPercentValue}%</Text>
                                        <Slider
                                            style={styles.slider}
                                            value={this.state.secondPercentValue}
                                            minimumValue={0}
                                            maximumValue={100}
                                            step={5}
                                            onValueChange={(newValue) => this.setState({ secondPercentValue: newValue })} />
                                    </View>
                                    <View style={{ flexDirection: 'row', alignItems: 'center', marginTop: 8 }}>
                                        <Text style={styles.flexLabel}>Percentage 3: {this.state.thirdPercentValue}%</Text>
                                        <Slider
                                            style={styles.slider}
                                            value={this.state.thirdPercentValue}
                                            minimumValue={0}
                                            maximumValue={100}
                                            step={5}
                                            onValueChange={(newValue) => this.setState({ thirdPercentValue: newValue })} />
                                    </View>
                                </View>
                            </TouchableWithoutFeedback>
                        </TouchableOpacity>
                    </Modal>
                </View>
            </View>
        );
    }

    onScreenTransitionValueChange = (itemValue, itemIndex) => {
        this.setState({ screenTransition: itemValue });
        this.saveTransitionValue(itemValue);
    }

    toggleModal = (visibled) => {
        this.setState({
            modalVisibled: visibled
        });

        if (!visibled) {
            this.savePercentage(this.state.firstPercentValue, this.state.secondPercentValue, this.state.thirdPercentValue);
        }
    }

    onRequestClose = () => {
        this.setState({
            modalVisibled: false
        });     
        
        this.savePercentage(this.state.firstPercentValue, this.state.secondPercentValue, this.state.thirdPercentValue);
    };

    async saveTransitionValue(transitionType) {
        try {
            await AsyncStorage.setItem('TRANSITION_VALUE', transitionType);
        } catch (error) {
            console.log(error);
        }
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

    async savePercentage(first, sec, third) {
        try {
            await AsyncStorage.setItem('PERCENT_1_VALUE', String(first));
            await AsyncStorage.setItem('PERCENT_2_VALUE', String(sec));
            await AsyncStorage.setItem('PERCENT_3_VALUE', String(third));
        } catch (error) {
            console.log(error);
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

module.exports = Settings;