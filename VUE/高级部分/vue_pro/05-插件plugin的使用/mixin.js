export const mix1 = {
    methods: {
        printInfo(){
           console.log(this.name, ',' , this.age) 
        }
    }
}

export const mix2 = {
    methods: {
        a(){
            console.log('mixin.js a.....')
            console.log('通过插件扩展的一个counter:', this.counter)
        }
    },
}

export const mix3 = {
    mounted() {
        console.log('mixin.js mounted...')
    }
}