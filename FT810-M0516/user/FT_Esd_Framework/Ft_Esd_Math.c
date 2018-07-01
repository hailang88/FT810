
#include "Ft_Esd_Math.h"

// #define ESD_RECT_STRICT (1) //< Results not guaranteed for inverted rectangles when disabled (width or height negative)

ft_bool_t Ft_Esd_Rect16_Intersects(Ft_Esd_Rect16 a, Ft_Esd_Rect16 b)
{
	return (b.X < (a.X + a.Width)) && (a.X < (b.X + b.Width))
		&& (b.Y < (a.Y + a.Height)) && (a.Y < (b.Y + b.Height));
}

ft_bool_t Ft_Esd_Rect16_IsInside(Ft_Esd_Rect16 subrect, Ft_Esd_Rect16 rect)
{
#ifdef ESD_RECT_STRICT
	return (subrect.X >= rect.X) && (subrect.X < (rect.X + rect.Width))
		&& ((subrect.X + subrect.Width) > rect.X) && ((subrect.X + subrect.Width) <= (rect.X + rect.Width))
		&& (subrect.Y >= rect.Y) && (subrect.Y < (rect.Y + rect.Height))
		&& ((subrect.Y + subrect.Height) >rect.Y) && ((subrect.Y + subrect.Height) <= (rect.Y + rect.Height));
#else
	return (subrect.X >= rect.X) && ((subrect.X + subrect.Width) <= (rect.X + rect.Width))
		&& (subrect.Y >= rect.Y) && ((subrect.Y + subrect.Height) <= (rect.Y + rect.Height));
#endif
}

ft_bool_t Ft_Esd_Rect16_IsInsideHorizontal(Ft_Esd_Rect16 subrect, Ft_Esd_Rect16 rect)
{
#ifdef ESD_RECT_STRICT
	return (subrect.X >= rect.X) && (subrect.X < (rect.X + rect.Width))
		&& ((subrect.X + subrect.Width) > rect.X) && ((subrect.X + subrect.Width) <= (rect.X + rect.Width));
#else
	return (subrect.X >= rect.X) && ((subrect.X + subrect.Width) <= (rect.X + rect.Width));
#endif
}

ft_bool_t Ft_Esd_Rect16_IsInsideVertical(Ft_Esd_Rect16 subrect, Ft_Esd_Rect16 rect)
{
#ifdef ESD_RECT_STRICT
	return (subrect.Y >= rect.Y) && (subrect.Y < (rect.Y + rect.Height))
		&& ((subrect.Y + subrect.Height) >rect.Y) && ((subrect.Y + subrect.Height) <= (rect.Y + rect.Height));
#else
	return (subrect.Y >= rect.Y) && ((subrect.Y + subrect.Height) <= (rect.Y + rect.Height));
#endif
}


/* end of file */
