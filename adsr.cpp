

class adsr
{
public:
    bool key;
    float attack;
    float decay;
    float sustain;
    float sustainLevel;
    float release;
    int sample;
    int sampleRate;

    float proces()
    {
        if (sample <= sampleRate * attack)
        {
            float a = 1 / (sample);
            return (sample * a);
        }
        if (sample < sampleRate * (attack + decay))
        {
            int b = 1;
            float a = (sustainLevel - b) / (sample);
            return (sample * a + b);
        }
        if (sample <= sampleRate * (attack + decay + sustain))
        {
            return sustainLevel;
        }
        if (sample < sampleRate * (attack + decay + sustain + release))
        {
            float b = sustainLevel;
            float a = (-b) / (sample);
            return (sample * a + b);
        }
    }
};
