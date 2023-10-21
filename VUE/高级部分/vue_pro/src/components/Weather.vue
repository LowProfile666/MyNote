<template>
    <div class="weather">
        <!-- 提示信息：您输入的城市名不存在 -->
        <div v-show="isNotFound">对不起，请检查您的城市名！</div>
        <div v-show="weather.isShow">
            <img :src="weather.imgPath" class="weather-icon">
            <h1 class="temp">{{weather.temp}}°c</h1>
            <h2 class="city">{{weather.city}}</h2>
            <div class="details">
                <div class="col">
                    <img src="../assets/images/humidity.png" />
                    <div>
                        <p class="humidity">{{weather.humidity}}%</p>
                        <p>湿度</p>
                    </div>
                </div>
                <div class="col">
                    <img src="../assets/images/wind.png">
                    <div>
                        <p class="wind">{{weather.windSpeed}} 米/秒</p>
                        <p>风速</p>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
	export default {
		name : 'Weather',
        data() {
            return {
                isNotFound : false,
                weather : {}
            }
        },
        methods: {
            displayWeather(weather, isNotFound){
                this.weather = weather
                this.isNotFound = isNotFound
            },
            displayNotFound(isNotFound){
                this.isNotFound = isNotFound
            }
        },
        mounted() {
            // 绑定事件
            this.$bus.$on('displayWeather', this.displayWeather)
            this.$bus.$on('displayNotFound', this.displayNotFound)
        },
	}
</script>

<style lang="css" scoped>
/*天气样式*/
.weather-icon {
    width: 170px;
    margin-top: 30px;
}

.weather h1 {
    font-size: 80px;
    font-weight: 500;
}

.weather h2 {
    font-size: 45px;
    font-weight: 400;
    margin-top: -10px;
}

.details {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0 20px;
    margin-top: 50px;
}

.col {
    display: flex;
    align-items: center;
    text-align: left;
}

.col img {
    width: 40px;
    margin-right: 10px;
}

.humidity, .wind {
    font-size: 28px;
    margin-top: -6px;
}
</style>