

class adsr
{
public:
    bool key;
    double attack;
    double decay;
    double sustain;
    double sustainLevel;
    double release;
    int sample;
    int sampleRate;

    double proces(){
        if (sample <= sampleRate*attack){
            double a = 1/(sample);
            return (sample * a);
        }
        if (sample < sampleRate*(attack + decay)){
            int b = 1;
            double a = (sustainLevel - b)/(sample);
            return (sample * a + b);
        }
        if (sample <= sampleRate*(attack + decay + sustain)){
            return sustainLevel; 
        }
        if (sample < sampleRate*(attack + decay + sustain + release)){
            double b = sustainLevel;
            double a = (-b)/(sample);
            return (sample * a + b);
        }
    }
};


