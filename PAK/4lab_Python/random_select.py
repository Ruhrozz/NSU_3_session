import numpy as np


def random_select1(real, syn, p):
    """
    Returns array with about p% synthetic data in stdout

    Parameters
    ----------
    real : numpy.ndarray
        The string which is to be reversed
    syn : numpy.ndarray
        The string which is to be concated
    p : float
        The string which is to be concated
    """
    rnd = np.random.sample(syn.size)
    print(np.where(rnd <= p, syn, real))


def random_select2(real, syn, p):
    """
        Returns array with about p% synthetic data in stdout

        Parameters
        ----------
        real : numpy.ndarray
            The string which is to be reversed
        syn : numpy.ndarray
            The string which is to be concated
        p : float
            The string which is to be concated
        """
    choices = [real, syn]
    rnd = np.random.rand(syn.size)
    print(np.choose(rnd <= p, choices))


def random_select3(real, syn, p):
    """
        Returns array with no more than p% synthetic data in stdout

        Parameters
        ----------
        real : numpy.ndarray
            The string which is to be reversed
        syn : numpy.ndarray
            The string which is to be concated
        p : float
            The string which is to be concated
        """
    rnd = np.random.randint(0, syn.size, size=round(p*syn.size))
    np.put(real, rnd, np.take(syn, rnd))
    print(real)


def random_select4(real, syn, p):
    """
        Returns array with about p% synthetic data in stdout

        Parameters
        ----------
        real : numpy.ndarray
            The string which is to be reversed
        syn : numpy.ndarray
            The string which is to be concated
        p : float
            The string which is to be concated
        """
    rng = np.random.default_rng()
    r_float = rng.random(real.size)
    choice_list = [real, syn]
    cond_list = [r_float > p, r_float <= p]
    print(np.select(cond_list, choice_list))


def random_select5(real, syn, p):
    """
        Returns array with exactly p% synthetic data in stdout

        Parameters
        ----------
        real : numpy.ndarray
            The string which is to be reversed
        syn : numpy.ndarray
            The string which is to be concated
        p : float
            The string which is to be concated
        """
    rnd = np.random.choice(syn.size, size=round(p*syn.size), replace=False)
    np.put(real, rnd, syn[rnd])
    print(real)


def random_select6(real, syn, p):
    """
        Returns array with about p% synthetic data in stdout

        Parameters
        ----------
        real : numpy.ndarray
            The string which is to be reversed
        syn : numpy.ndarray
            The string which is to be concated
        p : float
            The string which is to be concated
        """
    rnd = np.random.sample(syn.size)
    np.copyto(real, syn, where=(rnd <= p))
    print(real)


def random_select7(real, syn, p):
    """
        Returns array with about p% synthetic data in stdout

        Parameters
        ----------
        real : numpy.ndarray
            The string which is to be reversed
        syn : numpy.ndarray
            The string which is to be concated
        p : float
            The string which is to be concated
        """
    rnd = np.random.rand(syn.size)
    np.place(real, rnd <= p, syn)
    print(real)
